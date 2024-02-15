#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "carver.h"

bool first_h = true, first_v = true;
int h, w;
std::string const wnd_name = "carved";
std::string const h_bar_name = "horiz";
std::string const v_bar_name = "verti";
SeamCarver* p_carver;

void callback_h(int, void*);
void callback_v(int, void*);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Please give the path of image as an argument like "
                 "\"seam [path to img]\"\n";
  }

  auto const img = cv::imread(argv[1]);
  h = img.rows, w = img.cols;
  SeamCarver carver(img);
  p_carver = &carver;

  cv::namedWindow(wnd_name);
  {
    auto carved = carver.img();
    cv::imshow(wnd_name, carved);
  }
  cv::createTrackbar(h_bar_name, wnd_name, nullptr, h, callback_h);
  cv::setTrackbarPos(h_bar_name, wnd_name, h);
  cv::setTrackbarMin(h_bar_name, wnd_name, 2);
  cv::createTrackbar(v_bar_name, wnd_name, nullptr, w, callback_v);
  cv::setTrackbarPos(v_bar_name, wnd_name, w);
  cv::setTrackbarMin(v_bar_name, wnd_name, 2);
  cv::waitKey();
  return 0;
}

void callback_h(int, void*) {
  if (first_h) {
    first_h = false;
    return;
  }
  int const h_new = cv::getTrackbarPos(h_bar_name, wnd_name);
  if (h_new > h) {
    cv::setTrackbarPos(h_bar_name, wnd_name, h);
    return;
  } else if (h_new < h && h >= 3) {
    int const diff = h - h_new;
    for (int i = 0; i < diff; i++) {
      auto path = p_carver->find_h();
      p_carver->rm_h(path);
    }
    auto carved = p_carver->img();
    cv::imshow(wnd_name, carved);
    h = carved.rows;
    cv::setTrackbarPos(h_bar_name, wnd_name, h);
  }
}

void callback_v(int, void*) {
  if (first_v) {
    first_v = false;
    return;
  }
  int const w_new = cv::getTrackbarPos(v_bar_name, wnd_name);
  if (w_new > w) {
    cv::setTrackbarPos(v_bar_name, wnd_name, w);
    return;
  } else if (w_new < w && w >= 3) {
    int const diff = w - w_new;
    for (int i = 0; i < diff; i++) {
      auto path = p_carver->find_v();
      p_carver->rm_v(path);
    }
    auto carved = p_carver->img();
    cv::imshow(wnd_name, carved);
    w = carved.cols;
    cv::setTrackbarPos(h_bar_name, wnd_name, w);
  }
}
