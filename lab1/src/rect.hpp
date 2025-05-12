
class Rect {
  public:
    Rect();
    Rect(const Rect &other);
    Rect(int left, int right, int top, int bottom);
    ~Rect();

    int get_left() const;
    int get_right() const;
    int get_top() const;
    int get_bottom() const;

    void set_all(int left, int right, int top, int bottom);

    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_top, int d_bottom);

    void move(int x);
    void move(int x, int y);

    int get_width() const;
    int get_height() const;
    int get_square() const;

    void set_width(int width);
    void set_height(int height);

  private:
    // int left;
    // int right;
    // int top;
    // int bottom;

    int x;
    int y;
    int width;
    int height;

};