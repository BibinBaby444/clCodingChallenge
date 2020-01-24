#include "Subtitle_image.h"

int Subtitle_image::set_image(std::string&& img)
{
	std::string filename = id + ".png";
	std::string outputImage;
	std::ofstream out(filename);
	if(encoding == "Base64")
		outputImage = decode(img);
	else
		outputImage = img;
	out << outputImage;
	return outputImage.length();
}

std::string Subtitle_image::decode(std::string input)
{
  using namespace boost::archive::iterators;
  typedef transform_width<binary_from_base64<remove_whitespace
      <std::string::const_iterator> >, 8, 6> ItBinaryT;

  try
  {
    // If the input isn't a multiple of 4, pad with =
    size_t num_pad_chars((4 - input.size() % 4) % 4);
    input.append(num_pad_chars, '=');

    size_t pad_chars(std::count(input.begin(), input.end(), '='));
    std::replace(input.begin(), input.end(), '=', 'A');
    std::string output(ItBinaryT(input.begin()), ItBinaryT(input.end()));
    output.erase(output.end() - pad_chars, output.end());
    return output;
  }
  catch (std::exception const&)
  {
    return std::string("");
  }
}

