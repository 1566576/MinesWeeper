#pragma once
class Tile
{
public:
    Tile();
    ~Tile();
    void set_Mine(bool m) { m_mine = m; };
    bool get_Mine() { return m_mine; };
    void asign_Clicked(char m) { m_clicked = m; };
    void set_Square(char s) { m_square = s; };
    char get_Square() { return m_square; };
    char get_Clicked() { return m_clicked; };
private:
    bool m_mine;
    char m_square;
    char m_clicked;
};
