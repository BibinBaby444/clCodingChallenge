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

class Container {
private:
    std::vector<Atom> parent_atoms;
public:
    void addAtom(Atom& at)
    {
	parent_atoms.push_back(at);
    } 
};
#endif /* container_h */
