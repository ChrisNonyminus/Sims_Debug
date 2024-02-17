class MTObject {
  public:
    bool IsDynamic();
    short sub_408B4D(int);
};

bool MTObject::IsDynamic() { return sub_408B4D(8) != 0; }