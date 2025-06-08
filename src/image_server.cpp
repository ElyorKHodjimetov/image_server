#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "../libs/httplib.h"

using namespace std;
using namespace httplib;
using namespace cv; 


string get_image_extension(const Request& req) {
    auto ct = req.get_header_value("Content-Type");
    if (ct == "image/png")  
        return ".png";
    if (ct == "image/jpeg") 
        return ".jpg";
    return "";
}

Mat decode_image(const vector<uchar>& data) {
    return imdecode(data, IMREAD_COLOR);
}

Mat split_left(const Mat& img) {
    int halfW = img.cols / 2;
    return img(Rect(0, 0, halfW, img.rows)).clone();
}

vector<uchar> encode_image(const Mat& img, const string& ext) {
    vector<uchar> buf;
    if (ext == ".jpg") {
        imencode(ext, img, buf, { IMWRITE_JPEG_QUALITY, 90 });
    }
    else {
        imencode(ext, img, buf);
    }
    return buf;
}

void handle_process(const Request& req, Response& res) {
    string ext = get_image_extension(req);
    if (ext.empty()) {
        res.status = 415;
        res.set_content("Only PNG/JPEG supported", "text/plain");
        return;
    }

    vector<uchar> data(req.body.begin(), req.body.end());
    cout << "Received bytes: " << data.size() << "\n";

    Mat img = decode_image(data);
    if (img.empty()) {
        cout << "imdecode failed\n";
        res.status = 400;
        res.set_content("Failed to decode image", "text/plain");
        return;
    }
    cout << "imdecode succeeded: " << img.cols << "x" << img.rows << "\n";

    Mat left = split_left(img);

    auto out_buf = encode_image(left, ext);
    cout << "Sending bytes: " << out_buf.size() << "\n";

    res.status = 200;
    res.set_header("Content-Type", ext == ".jpg" ? "image/jpeg" : "image/png");
    res.body.assign(reinterpret_cast<char*>(out_buf.data()), out_buf.size());
}

int main() {
    cout << "Server starting...\n";

    Server svr;

    svr.Get("/ping", [](const Request&, Response& res) {
        res.set_content("pong", "text/plain");
        });

    svr.Post("/process", handle_process);

    cout << "Server listening on http://0.0.0.0:8080\n";
    svr.listen("0.0.0.0", 8080);

    return 0;
}
