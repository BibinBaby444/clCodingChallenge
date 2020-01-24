//
//  atom.h
//  mp4parse
//
//  Created by Bibin Baby on 22/01/20.
//  Copyright © 2020 Bibin Baby. All rights reserved.
//

#ifndef Atom_h
#define Atom_h

#include <vector>
#include <list>
#include <iostream>
#include "Subtitle_image.h"

class Atom {
private:
    std::string _name;
    long _length;
    std::vector<char> _content;
    std::vector<Atom> _sub_atoms;
public:
    Atom(std::string name = "none",long length = 0) : _name{name},_length{length} {}
    std::string atom_name(){ return _name;}
    long atom_length (){ return _length;}
    void set_sub_atom ( Atom&& box )
    {
        _sub_atoms.push_back(std::move(box));
    }
    virtual void set_content(std::vector<char> content)
    {
        _content = content;
    }
};

class Subt_mdat : public Atom
{
private: 
	std::list<Subtitle_image> _mlist;
public:
	Subt_mdat(std::string name = "mdat",long length = 0):Atom(name,length){}
	
	void set_content(std::vector<char> content_v) override;
};
#endif /* Atom_h */
