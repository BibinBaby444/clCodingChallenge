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

int main(void) {
    Downloader dd;
    std::vector<char> mp4buf;
    long total_file_size = dd.startDownload(mp4buf);
    //std::cout<<"Downloaded file size = "<<total_file_size<<std::endl;
    if (total_file_size)
    {
	    Container cntnr;
	    cntnr.create_atom_tree(mp4buf);
    }
    return 0;
}
