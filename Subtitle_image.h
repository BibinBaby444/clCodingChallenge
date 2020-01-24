//
//  Subtitle_image.h
//  mp4parse
//
//  Created by Bibin Baby on 22/01/20.
//

#ifndef Subtitle_image_h
#define Subtitle_image_h

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>
#include <algorithm>    
#include <fstream>

class Subtitle_image
{
private:
	std::string id;
	std::string encoding;
	std::string decode(std::string input);
//	std::map<std::pair<std::string,std::shared<std::ofstream>>> streams;  
public:
	Subtitle_image(std::string idx = "none",std::string encodingP = "Base64"):id{idx},encoding{encodingP} {}
	int set_image(std::string&& img);		
};
#endif /* Subtitle_image_h */

