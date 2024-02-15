#ifndef __SEAM_CARVER_H__
#define __SEAM_CARVER_H__

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <opencv2/highgui.hpp>
#include <utility>
#include <vector>

class SeamCarver {
  cv::Mat img_;
  cv::Mat img_e_;  // energy image
  uint64_t H_;     // height of image
  uint64_t W_;     // width of image
  constexpr static double E_CONER =
      1000.0;  // edge-pixel energy (`>` interior ones)
  constexpr static double POS_INF = std::numeric_limits<double>::max();
  enum Axis : uint8_t {
    X,
    Y,
  };

 public:
  SeamCarver(cv::Mat const& img) {
    assert(img.type() == CV_8U || img.type() == CV_8UC3);
    img_ = img.clone();
    H_ = img_.rows;
    W_ = img_.cols;
    update_energy();
  }

  cv::Mat img() const { return img_.clone(); }

  uint64_t H() const { return H_; };
  uint64_t W() const { return W_; };

  std::vector<uint64_t> find_h() const { return find_path(Axis::Y); };
  std::vector<uint64_t> find_v() const { return find_path(Axis::X); };

  void rm_h(std::vector<uint64_t> const& path) {
    assert(path.size() == W_);
    assert(H_ >= 3);
    rm_path(path, Axis::Y);
  };
  void rm_v(std::vector<uint64_t> const& path) {
    assert(path.size() == H_);
    assert(W_ >= 3);
    rm_path(path, Axis::X);
  };

 private:
  double energy(uint64_t const x, uint64_t const y) const {
    assert(x < H_ && y < W_);
    return dural_gradient(x, y);
  }

  double dural_gradient(uint64_t const x, uint64_t const y) const {
    if (x == 0 || x == H() - 1 || y == 0 || y == W() - 1) {
      return E_CONER;
    }
    if (img_.type() == CV_8U) {
      uint8_t const left = img_.at<uint8_t>(x, y - 1),
                    right = img_.at<uint8_t>(x, y + 1),
                    up = img_.at<uint8_t>(x - 1, y),
                    down = img_.at<uint8_t>(x + 1, y);
      return std::sqrt(diff2(left, right) + diff2(up, down));
    } else {
      // `img_.type()` is `CV_8UC3`
      cv::Vec3b const left = img_.at<cv::Vec3b>(x, y - 1),
                      right = img_.at<cv::Vec3b>(x, y + 1),
                      up = img_.at<cv::Vec3b>(x - 1, y),
                      down = img_.at<cv::Vec3b>(x + 1, y);
      return std::sqrt(diff2(left, right) + diff2(up, down));
    }
  }

  double diff2(uint8_t const lhs, uint8_t const rhs) const {
    return std::pow((double)lhs - (double)rhs, 2.0);
  }

  double diff2(cv::Vec3b const lhs, cv::Vec3b const rhs) const {
    return std::pow((double)lhs[0] - (double)rhs[0], 2.0) +
           std::pow((double)lhs[1] - (double)rhs[1], 2.0) +
           std::pow((double)lhs[2] - (double)rhs[2], 2.0);
  }

  std::vector<uint64_t> find_path(Axis const a) const {
    std::vector<uint64_t> vertex_to(H_ * W_, 0);
    uint64_t min_idx = broadcast(vertex_to, a);
    return backtrace(vertex_to, min_idx, a);
  }

  // broadcast along the axis. take horizontal as example:
  // if y >= 1 (y = 0, 1, ...)
  // min_e(x,y) = min{min_e(x-1,y-1), min_e(x,y-1), min_e(x+1,y-1)} + e(x,y)
  uint64_t broadcast(std::vector<uint64_t>& vertex_to, Axis const a) const {
    uint64_t min_idx = 0;
    double min_e = POS_INF;
    std::vector<double> total_energy(H_ * W_, 0.0);

    if (a == Axis::Y) {
      // initilize the start line energy
      for (uint64_t r = 0; r < H_; r++) {
        total_energy[r * W_ + 0] = img_e_.at<double>(r, 0);
      }
      for (uint64_t c = 1; c < W_; c++) {
        for (uint64_t r = 0; r < H_; r++) {
          std::array<double, 3> tmp_e;
          tmp_e[0] = r == 0 ? POS_INF : total_energy[(r - 1) * W_ + (c - 1)];
          tmp_e[1] = total_energy[r * W_ + (c - 1)];
          tmp_e[2] =
              r == H_ - 1 ? POS_INF : total_energy[(r + 1) * W_ + (c - 1)];
          auto const [val, idx] = min3(tmp_e);

          // update the min energy as seam goes through (x,y)
          total_energy[r * W_ + c] = val + img_e_.at<double>(r, c);
          vertex_to[r * W_ + c] = r + idx - 1;
        }
      }
      for (uint64_t r = 0; r < H_; r++) {
        double const e = total_energy[r * W_ + (W_ - 1)];
        if (e < min_e) {
          min_e = e;
          min_idx = r;
        }
      }
    } else {
      // vertical
      for (uint64_t c = 0; c < W_; c++) {
        total_energy[0 * W_ + c] = img_e_.at<double>(0, c);
      }
      for (uint64_t r = 1; r < H_; r++) {
        for (uint64_t c = 0; c < W_; c++) {
          std::array<double, 3> tmp_e;
          tmp_e[0] = c == 0 ? POS_INF : total_energy[(r - 1) * W_ + (c - 1)];
          tmp_e[1] = total_energy[(r - 1) * W_ + c];
          tmp_e[2] =
              c == W_ - 1 ? POS_INF : total_energy[(r - 1) * W_ + (c + 1)];
          auto const [val, idx] = min3(tmp_e);

          // update the min energy as seam goes through (x,y)
          total_energy[r * W_ + c] = val + img_e_.at<double>(r, c);
          vertex_to[r * W_ + c] = c + idx - 1;
        }
      }
      for (uint64_t c = 0; c < W_; c++) {
        double const e = total_energy[(H_ - 1) * W_ + c];
        if (e < min_e) {
          min_e = e;
          min_idx = c;
        }
      }
    }
    return min_idx;
  }

  // collect vertices starting from min_idx
  std::vector<uint64_t> backtrace(std::vector<uint64_t> const& vertex_to,
                                  uint64_t const min_idx,
                                  Axis const a) const {
    std::vector<uint64_t> path;
    if (a == Axis::Y) {
      path.reserve(W_);
      path.push_back(min_idx);
      for (uint64_t last_c = W_ - 1; last_c != 0; last_c--) {
        uint64_t const last_r = path.back();
        uint64_t const c = last_c - 1;
        uint64_t const r = vertex_to[last_r * W_ + last_c];
        path.push_back(vertex_to[r * W_ + c]);
      }
    } else {
      // vertical
      path.reserve(H_);
      path.push_back(min_idx);
      for (uint64_t last_r = H_ - 1; last_r != 0; last_r--) {
        uint64_t const last_c = path.back();
        uint64_t const r = last_r - 1;
        uint64_t const c = vertex_to[last_r * W_ + last_c];
        path.push_back(vertex_to[r * W_ + c]);
      }
    }
    std::reverse(path.begin(), path.end());
    return path;
  }

  std::pair<double, uint64_t> min3(std::array<double, 3> const& arr) const {
    double val = arr[0];
    uint64_t idx = 0;
    if (arr[1] < val) {
      val = arr[1];
      idx = 1;
    }
    if (arr[2] < val) {
      val = arr[2];
      idx = 2;
    }
    return std::make_pair(val, idx);
  }

  void rm_path(std::vector<uint64_t> path, Axis const a) {
    cv::Mat img;
    if (a == Axis::Y) {
      img = cv::Mat::zeros(H_ - 1, W_, img_.type());
      uint64_t i = 0;
      for (uint64_t c = 0, c0 = 0; c0 < W_; c0++) {
        for (uint64_t r = 0, r0 = 0; r0 < H_; r0++) {
          if (c0 == i && r0 == path[i]) {
            i++;
            continue;
          }
          if (img_.type() == CV_8UC1) {
            img.at<uint8_t>(r, c) = img_.at<uint8_t>(r0, c0);
          } else {
            img.at<cv::Vec3b>(r, c) = img_.at<cv::Vec3b>(r0, c0);
          }
          r++;
        }
        c++;
      }
    } else {
      // vertical
      img = cv::Mat::zeros(H_, W_ - 1, img_.type());
      uint64_t i = 0;
      for (uint64_t r = 0, r0 = 0; r0 < H_; r0++) {
        for (uint64_t c = 0, c0 = 0; c0 < W_; c0++) {
          if (r0 == i && c0 == path[i]) {
            i++;
            continue;
          }
          if (img_.type() == CV_8UC1) {
            img.at<uint8_t>(r, c) = img_.at<uint8_t>(r0, c0);
          } else {
            img.at<cv::Vec3b>(r, c) = img_.at<cv::Vec3b>(r0, c0);
          }
          c++;
        }
        r++;
      }
    }

    // update img and energy img
    img_ = img;
    H_ = img_.rows;
    W_ = img_.cols;
    update_energy();
  }

  void update_energy() {
    img_e_ = cv::Mat::zeros(H_, W_, CV_64FC1);
    for (uint64_t r = 0; r < H_; r++) {
      for (uint64_t c = 0; c < W_; c++) {
        img_e_.at<double>(r, c) = energy(r, c);
      }
    }
  }
};

#endif  // !__SEAM_CARVER_H__
