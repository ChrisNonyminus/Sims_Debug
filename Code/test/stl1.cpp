#include <bstring.h>
#include <vector.h>

vector<char>::vector_allocator vector<char>::static_allocator;
vector<string>::vector_allocator vector<string>::static_allocator;

void main() {
  vector<string> v;
  v.push_back("Hello world");
  int len = v.size();
}
