#include <gtest/gtest.h>

#include <algorithm>
#include <memory>

TEST(uniptr, test) {
  class TestClass {
   public:
    class Node {
     public:
      int x_, y_;
      std::string name_;
      std::unique_ptr<Node> next_;

      Node(int x, int y, std::string const& name)
          : x_{x}, y_{y}, name_{name}, next_{nullptr} {
        std::cout << "constructing node " << name_ << '\n';
      };

      ~Node() { std::cout << "deconstructing node " << name_ << '\n'; }
    };

   private:
    std::unique_ptr<Node> root_;

   public:
    TestClass() : root_{nullptr} { std::cout << "constructing test class\n"; }

    void put(int x, int y, std::string const& name) {
      if (root_ == nullptr) {
        root_ = std::make_unique<Node>(x, y, name);
        return;
      }
      Node* curr = root_.get();
      while (curr) {
        if (curr->next_ == nullptr) {
          curr->next_ = std::make_unique<Node>(x, y, name);
          return;
        }
        curr = curr->next_.get();
      }
    }

    std::unique_ptr<Node> get() {
      if (root_ == nullptr)
        return nullptr;
      std::unique_ptr<Node> ret = std::move(root_);
      root_ = std::move(ret->next_);
      return ret;
    }
  };

  std::unique_ptr<TestClass::Node> p;
  {
    TestClass t;
    t.put(1, 1, "node 1");
    t.put(1, 2, "node 2");
    p = t.get();
    EXPECT_EQ(p->x_, 1);
    EXPECT_EQ(p->y_, 1);
    EXPECT_EQ(p->name_, std::string{"node 1"});
  }
  EXPECT_EQ(p->x_, 1);
  EXPECT_EQ(p->y_, 1);
  EXPECT_EQ(p->name_, std::string{"node 1"});
}

TEST(assign_by_const, test) {
  class TestClass {
   private:
    int x_ = 0;

   public:
    TestClass() : x_{0} { std::cout << "default construct\n"; }

    TestClass(TestClass const& rhs) : x_{rhs.x_} {
      std::cout << "copy construct\n";
    }

    TestClass& operator=(TestClass const& rhs) {
      std::cout << "copy assignment construct\n";
      if (&rhs != this) {
        TestClass tmp = TestClass(rhs);
        std::swap(tmp.x_, x_);
      }
      return *this;
    }
  };

  TestClass node1;
  TestClass node2;
  TestClass node3(node2);
  TestClass node4 = node2;
  TestClass node5 = node2;

  TestClass const node6 = node2;
  TestClass const node7;
}

TEST(copy, test) {
  class Node {
   public:
    std::string name_;

    Node(std::string& name) : name_{name} {}
  };

  std::string str = std::string{"str1"};
  std::unique_ptr<Node> np = std::make_unique<Node>(str);
  std::cout << "address of str " << &str << '\n';
  std::cout << "address of unique pointer " << &np.get()->name_ << '\n';
  str = std::string{"str2"};
  std::cout << "content of Node string " << np.get()->name_ << '\n';
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
