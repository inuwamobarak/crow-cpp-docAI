#include <crow_all.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/inference")
        .methods("POST"_method)
        ([](const crow::request& req) {
            crow::json::wvalue response;

            // Handle form data
            auto prompt = req.body["prompt"].s();
            auto image_data = req.body["image"].s();

            // Save image data to a file
            ofstream image_file("temp_image.png", ios::binary);
            image_file << image_data;
            image_file.close();

            // auto result = perform_inference(prompt, "temp_image.png");

            response["result"] = "Inference result goes here";

            return crow::response(response);
        });

    // Serve static files (e.g., index.html)
    CROW_ROUTE(app, "/")
        .methods("GET"_method)
        ([]() {
            ifstream file("index.html");
            if (!file.is_open()) {
                return crow::response(500, "Internal Server Error");
            }

            stringstream buffer;
            buffer << file.rdbuf();
            file.close();

            return crow::response(buffer.str());
        });

    app.port(8080).multithreaded().run();  // Change port as needed

    return 0;
}