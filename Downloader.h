//
//  Download.h
//  mp4parse
//
//  Created by Bibin Baby on 22/01/20.
//  Copyright © 2020 Bibin Baby. All rights reserved.
//

#ifndef Download_h
#define Download_h

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <vector>

class Downloader {
private:
    std::string _url;
    long _total_download_bytes;
public:
    Downloader(std::string name = "http://demo.castlabs.com/tmp/text0.mp4") : _url(name),_total_download_bytes(0) {}
    long startDownload(std::vector<char> &downloadBuffer);
    void stopDownload() {}
    void pauseDownload() {}
    void restartDownload() {}
};
#endif /* Download_h */
