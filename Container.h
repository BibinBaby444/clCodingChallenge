//
//  Container.h
//  mp4parse
//
//  Created by Bibin Baby on 22/01/20.
//  Copyright © 2020 Bibin Baby. All rights reserved.
//

#ifndef Container_h
#define Container_h

#include <vector>
#include <iostream>
#include "Atom.h"

class Container {
private:
    std::vector<Atom> parent_atoms;
    void add_sub_atoms(std::vector<char> & atombuf,Atom& atm);
    long get_atom_length(std::string& str);
public:
    void create_atom_tree(std::vector<char> & mp4buf);
    void addAtom(Atom& at)
    {
	parent_atoms.push_back(at);
    } 
};
#endif /* container_h */
