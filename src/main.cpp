#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../libs/httplib.h"

using namespace httplib;

int main() {
    std::cout << "Server starting...\n";

    Server svr;

    // GET /ping
    svr.Get("/ping", [](const Request&, Response& res) {
        res.set_content("pong", "text/plain");
        });

    // POST /process с логами
    svr.Post("/process", [](const Request& req, Response& res) {
        auto ct = req.get_header_value("Content-Type");
        std::cout << "[DBG] Content-Type: " << ct << "\n";

        // Читаем всё тело
        std::vector<uchar> data(req.body.begin(), req.body.end());
        std::cout << "[DBG] Received bytes: " << data.size() << "\n";

        // Декодируем
        cv::Mat img = cv::imdecode(data, cv::IMREAD_COLOR);
        if (img.empty()) {
            std::cout << "[DBG] imdecode failed\n";
            res.status = 400;
            res.set_content("Failed to decode image", "text/plain");
            return;
        }

        // Разрезаем
        int halfW = img.cols / 2;
        cv::Mat left = img(cv::Rect(0, 0, halfW, img.rows));

        // Кодируем обратно
        std::vector<uchar> out;
        if (ct == "image/jpeg") {
            cv::imencode(".jpg", left, out, { cv::IMWRITE_JPEG_QUALITY, 90 });
            res.set_header("Content-Type", "image/jpeg");
        }
        else {
            cv::imencode(".png", left, out);
            res.set_header("Content-Type", "image/png");
        }
        std::cout << "[DBG] Sending bytes: " << out.size() << "\n";

        res.status = 200;
        res.body.assign(reinterpret_cast<char*>(out.data()), out.size());
        });

    std::cout << "Server listening on http://0.0.0.0:8080\n";
    svr.listen("0.0.0.0", 8080);
    return 0;
}
