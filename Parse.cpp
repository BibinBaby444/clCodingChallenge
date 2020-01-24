//
//  main.cpp
//  mp4parse
//
//  Created by Bibin Baby on 22/01/20.
//  Copyright © 2020 Bibin Baby. All rights reserved.
//

#include <string>
#include <fstream>
#include <iostream>
#include "Atom.h"
#include "Downloader.h"
#include "Container.h"

long get_atom_length(std::string& str)
{
    std::vector<long> bytes(str.begin(), str.end());
    long atom_length = ((bytes[0] << 24 ) | (bytes[1] << 16 ) | (bytes[2] << 8 ) | (bytes[3]  & 0xFF));
    
    return atom_length;
}

void add_sub_atoms(std::vector<char> & mp4buf,Atom& atm)
{
    long parse_len = 4;
    long parse_start = 0;
    while(parse_start != mp4buf.size())
    {
        parse_len = 4;
        std::string atom_length_s ( &mp4buf[parse_start],&mp4buf[parse_start + parse_len] );
        long atom_length = get_atom_length(atom_length_s);
        parse_start += parse_len;
        parse_len = 4;
        std::string atom_name_s ( &mp4buf[parse_start],&mp4buf[parse_start + parse_len] );
        std::cout<<"Found box of type "<<atom_name_s<<" and size "<<atom_length<<std::endl;
        parse_start += parse_len;
        parse_len = (atom_length - 8);
        Atom at(atom_name_s,atom_length);
        std::vector<char> content{ &mp4buf[parse_start],&mp4buf[parse_start + parse_len] };
        at.set_content(content);
        parse_start += parse_len;
        if((atom_name_s == "moof")||(atom_name_s == "traf"))
                add_sub_atoms(content,at);
        atm.set_sub_atom(std::move(at));
    }
}

void create_atom_tree(std::vector<char> & mp4buf,Container& ctn)
{
    size_t parse_len = 4;
    size_t parse_start = 0;
    while(parse_start != mp4buf.size())
    {
        parse_len = 4;
        std::string atom_length_s ( &mp4buf[parse_start],&mp4buf[parse_start + parse_len] );
        long atom_length = get_atom_length(atom_length_s);
        parse_start += parse_len;
        parse_len = 4;
        std::string atom_name_s ( &mp4buf[parse_start],&mp4buf[parse_start + parse_len]);
        std::cout<<"Found box of type "<<atom_name_s<<" and size "<<atom_length<<std::endl;
        parse_start += parse_len;
        parse_len = (atom_length - 8);
	std::vector<char> content { &mp4buf[parse_start],&mp4buf[parse_start + parse_len]};
	if(atom_name_s == "mdat")
	{
		Subt_mdat at(atom_name_s,atom_length);
		at.set_content(content);
        	ctn.addAtom(at);
	}
	else
	{	
        	Atom at(atom_name_s,atom_length);
        	at.set_content(content);
		if((atom_name_s == "moof")||(atom_name_s == "traf"))
			add_sub_atoms(content,at);
        	ctn.addAtom(at);
	}
        parse_start += parse_len;
    }
}

int main(void) {
    Downloader dd;
    std::vector<char> mp4buf;
    long total_file_size = dd.startDownload(mp4buf);
    //std::cout<<"Downloaded file size = "<<total_file_size<<std::endl;
    if (total_file_size)
    {
	    Container cntnr;
	    create_atom_tree(mp4buf,cntnr);
    }
    return 0;
}
