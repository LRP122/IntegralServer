class Function{
public:
    float y;
    float virtual function(float x){return 0.0;}
    float e;

public:
    float e_function() {
        for(int i=0 ; i < 50 ; i++){
            e += 1/factorial(i);
        }
        return e;
    }

private:
   float factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
    }
};

class quadratic_function : public Function{
public:
    float y;
    virtual float function(float x) override{
        y = x * x;
        return y;
    }
};

class exponential_function : public Function{
public:
    float y;
    float e = Function::e_function();


    virtual float function(float x) override {
        return y = pow(e,x);
    }
};

class gaussian_function : public Function {

    float e = Function::e_function();

    virtual float function(float x) override {
        return y = pow(e,pow(x,2));
    }
};