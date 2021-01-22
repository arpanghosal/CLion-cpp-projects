class Polygon {
public:
    Polygon(int n, float radius);
    virtual ~Polygon(){};
    float computePerimeter();
protected:
    int m_nbSides;
    int m_radius;
};

class Hexagon : public Polygon {
public:
    Hexagon(char* name, float radius);
    ~Hexagon();
    char* name() const {return m_name;};
private:
    char* m_name;
};
