class Barrel {
    private:
        double volume;         
        double concentration;
    public:
        Barrel(double init_volume, double init_concentration);
    
        void pourInto(Barrel &other, double amount);
        double getConcentration() const;
        double getVolume() const;
    };