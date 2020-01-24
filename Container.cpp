//Adding Parent Atoms and it's sub atoms into the container

#include "Container.h"

long Container::get_atom_length(std::string& str)
{
    std::vector<long> bytes(str.begin(), str.end());
    long atom_length = ((bytes[0] << 24 ) | (bytes[1] << 16 ) | (bytes[2] << 8 ) | (bytes[3]  & 0xFF));

    return atom_length;
}

void Container::add_sub_atoms(std::vector<char> & mp4buf,Atom& atm)
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

void Container::create_atom_tree(std::vector<char> & mp4buf)
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
                addAtom(at);
        }
        else
        {
                Atom at(atom_name_s,atom_length);
                at.set_content(content);
                if((atom_name_s == "moof")||(atom_name_s == "traf"))
                        add_sub_atoms(content,at);
                addAtom(at);
        }
        parse_start += parse_len;
    }
}

