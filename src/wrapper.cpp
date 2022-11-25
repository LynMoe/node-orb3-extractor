#include <node_api.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <vector>
#include <iostream>

#include "ORBextractor.h"

using namespace ORB_SLAM3;

napi_value computeORB3(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 2;
  napi_value argv[2];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  char filename[255];
  size_t result;
  status = napi_get_value_string_utf8(env, argv[0], filename, 255, &result);

  char configString[100];
  status = napi_get_value_string_utf8(env, argv[1], configString, 100, &result);

  // split configString
  std::vector<std::string> config;
  {
    std::string str(configString);
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ',')) {
      config.push_back(token);
    }
  }
  int nfeatures = std::stoi(config[0]);
  float scaleFactor = std::stof(config[1]);
  int nlevels = std::stoi(config[2]);
  int iniThFAST = std::stoi(config[3]);
  int minThFAST = std::stoi(config[4]);

  ORBextractor orb3 = ORBextractor(nfeatures, scaleFactor, nlevels, iniThFAST, minThFAST);

  cv::Mat image = cv::imread(filename, cv::IMREAD_GRAYSCALE);
  cv::Mat mask;
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat descriptors;
  std::vector<int> vLappingArea;
  vLappingArea.push_back(0);
  vLappingArea.push_back(0);

  orb3(image, mask, keypoints, descriptors, vLappingArea);

  std::string descriptorsString = "";
  for (int i = 0; i < descriptors.rows; i++) {
    for (int j = 0; j < descriptors.cols; j++) {
      descriptorsString += std::to_string(descriptors.at<uchar>(i, j));
      descriptorsString += ",";
    }
    descriptorsString += ";";
  }

  std::string keypointsString = "";
  for (int i = 0; i < keypoints.size(); i++) {
    keypointsString += std::to_string(keypoints[i].pt.x);
    keypointsString += ",";
    keypointsString += std::to_string(keypoints[i].pt.y);
    keypointsString += ",";
    keypointsString += std::to_string(keypoints[i].size);
    keypointsString += ",";
    keypointsString += std::to_string(keypoints[i].angle);
    keypointsString += ",";
    keypointsString += std::to_string(keypoints[i].response);
    keypointsString += ",";
    keypointsString += std::to_string(keypoints[i].octave);
    keypointsString += ",";
    keypointsString += std::to_string(keypoints[i].class_id);
    keypointsString += ";";
  }

  napi_value resultValue;
  status = napi_create_string_utf8(env, (descriptorsString + "&" + keypointsString).c_str(), NAPI_AUTO_LENGTH, &resultValue);

  return resultValue;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, NULL, 0, computeORB3, NULL, &fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }

  status = napi_set_named_property(env, exports, "computeORB3", fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
