//Downloader class Function that downloads the content from a URL to a 
//vector of characters
#include "Downloader.h"

long Downloader::startDownload(std::vector<char> &downloadBuffer)
{
	CURL *curl;
	CURLcode res;
	std::string url{_url};
	//      std::ofstream outfilename (_outfilename,std::ios::binary);
	static long total_download_bytes = 0;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
		+[](char *ptr, size_t size, size_t nmemb, void *userdata)
			{
			    //std::ofstream *out = static_cast<std::ofstream *>(userdata);
			    std::vector<char> *out = static_cast<std::vector<char> *>(userdata);
			    size_t nbytes = size * nmemb;
			    total_download_bytes += nbytes;
			    //out->write(ptr, nbytes);
			    for(int i = 0;i < nbytes;i++)
				(*out).push_back(ptr[i]);
			    return nbytes;
			}
		);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outfilename);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &downloadBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	if(res == CURLE_OK)
	{
		std::cout<<"Successfully loaded file "<<url<<std::endl;
		_total_download_bytes = total_download_bytes;
	}
	return total_download_bytes;
}

