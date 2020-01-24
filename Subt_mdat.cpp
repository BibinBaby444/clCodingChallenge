// Parsing individual subtitle image frames

#include "Atom.h"

void Subt_mdat::set_content(std::vector<char> content_v)
{
	size_t start;
	size_t end;
	size_t len;
	std::string content {content_v.begin(),content_v.end()};
	std::cout<<"Content of mdat box is: "<<content<<std::endl;
	//Assuming mdat is of type image subtitles
	start = 0;
	while(start != std::string::npos)
	{
		std::string id;
		std::string enc;
		std::string img;
		std::string id_string {"<smpte:image xml:id=\""};
		start = content.find(id_string,start);
		if(start != std::string::npos)
		{
			start += id_string.length();
			end = content.find("\"",start);
			len = (end == std::string::npos)? std::string::npos : end - start;
			id = content.substr(start, len);
		}
		else
			break;

		std::string enc_string {"encoding=\""};
		start = content.find(enc_string,end);
		if(start != std::string::npos)
		{
			start += enc_string.length();
			end = content.find("\"",start);
			len = (end == std::string::npos)? std::string::npos : end - start;
			enc = content.substr(start, len);
		}
		Subtitle_image image(id,enc);

		std::string img_string {">"};
		start = content.find(img_string,end);
		if(start != std::string::npos)
		{
			start += img_string.length();
			end = content.find("</smpte:image>",start);
			len = (end == std::string::npos)? std::string::npos : end - start;
			img = content.substr(start, len);
		}
		image.set_image(std::move(img));
		_mlist.push_back(image);
	}
}
