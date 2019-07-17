#include "color.h"
#include "util.h"

Color::Color(int r, int g, int b, float a) :
R((float)r/255.0), G((float)g/255.0), B((float)b/255.0), A(a)
{
    correct();
}

Color::Color(float r, float g, float b, float a) :
R(r), G(g), B(b), A(a)
{
    correct();
}

Color::Color(double r, double g, double b, double a) :
R((float)r), G((float)g), B((float)b), A((float)a)
{
    correct();
}

Color::Color(const char* name)
{
    name = lower(name);
    if(strcmp(name, "red") == 0 || strcmp(name, "r") == 0)
    {
        R = 1.0f;
        // G = 0.0f;
        // B = 0.0f;
    }
    else if(strcmp(name, "green") == 0 || strcmp(name, "g") == 0)
    {
        // R = 0.0f;
        G = 1.0f;
        // B = 0.0f;
    }
    else if(strcmp(name, "blue") == 0 || strcmp(name, "b") == 0)
    {
        // R = 0.0f;
        // G = 0.0f;
        B = 1.0f;
    }
    else if(strcmp(name, "cyan") == 0 || strcmp(name, "c") == 0)
    {
        // R = 0.0f;
        G = 1.0f;
        B = 1.0f;
    }
    else if(strcmp(name, "magenta") == 0 || strcmp(name, "m") == 0)
    {
        R = 1.0f;
        // G = 0.0f;
        B = 1.0f;
    }
    else if(strcmp(name, "yellow") == 0 || strcmp(name, "y") == 0)
    {
        R = 1.0f;
        G = 1.0f;
        // B = 0.0f;
    }
    else if(strcmp(name, "white") == 0 || strcmp(name, "w") == 0)
    {
        R = 1.0f;
        G = 1.0f;
        B = 1.0f;
    }
}

Color::Color(string name)
{
    name = lower(name);
    if(name == "red" || name == "r")
    {
        R = 1.0f;
        // G = 0.0f;
        // B = 0.0f;
    }
    else if(name == "green" || name == "g")
    {
        // R = 0.0f;
        G = 1.0f;
        // B = 0.0f;
    }
    else if(name == "blue" || name == "b")
    {
        // R = 0.0f;
        // G = 0.0f;
        B = 1.0f;
    }
    else if(name == "cyan" || name == "c")
    {
        // R = 0.0f;
        G = 1.0f;
        B = 1.0f;
    }
    else if(name == "magenta" || name == "m")
    {
        R = 1.0f;
        // G = 0.0f;
        B = 1.0f;
    }
    else if(name == "yellow" || name == "y")
    {
        R = 1.0f;
        G = 1.0f;
        // B = 0.0f;
    }
    else if(name == "white" || name == "w")
    {
        R = 1.0f;
        G = 1.0f;
        B = 1.0f;
    }
}

Color::Color(char name)
{
    switch(name)
    {
        case 'r': R = 1.0f; break;
        case 'g': G = 1.0f; break;
        case 'b': B = 1.0f; break;
        case 'c': G = B = 1.0f; break;
        case 'm': R = B = 1.0f; break;
        case 'y': R = G = 1.0f; break;
        case 'w': R = G = B = 1.0f; break;
        default: break;
    }
}

inline void to01(float& x)
{
    x = (x > 0 ? (x < 1 ? x : 1) : 0);
}

void Color::correct()
{
    to01(R);
    to01(G);
    to01(B);
    to01(A);
}

Color operator +(const Color& c1, const Color& c2)
{
    Color c;
    c.R = c1.R + c2.R;
    c.G = c1.G + c2.G;
    c.B = c1.B + c2.B;
    c.A = c1.A + c2.A;
    c.correct();

    return c;
}

Color operator -(const Color& c1, const Color& c2)
{
    Color c;
    c.R = c1.R - c2.R;
    c.G = c1.G - c2.G;
    c.B = c1.B - c2.B;
    c.A = c1.A - c2.A;
    c.correct();

    return c;
}

Color operator *(const Color& c1, const Color& c2)
{
    Color c;
    c.R = c1.R * c2.R;
    c.G = c1.G * c2.G;
    c.B = c1.B * c2.B;
    c.A = c1.A * c2.A;

    return c;
}

Color operator /(const Color& c1, const Color& c2)
{
    Color c;
    c.R = (c2.R != 0 ? c1.R / c2.R : 1);
    c.G = (c2.G != 0 ? c1.G / c2.G : 1);
    c.B = (c2.B != 0 ? c1.B / c2.B : 1);
    c.A = (c2.A != 0 ? c1.A / c2.A : 1);
    c.correct();

    return c;
}

Color operator +(float k, const Color& c2)
{
    Color c;
    c.R = k + c2.R;
    c.G = k + c2.G;
    c.B = k + c2.B;
    c.A = k + c2.A;
    c.correct();

    return c;
}

Color operator -(float k, const Color& c2)
{
    Color c;
    c.R = k - c2.R;
    c.G = k - c2.G;
    c.B = k - c2.B;
    c.A = k - c2.A;
    c.correct();

    return c;
}

Color operator *(float k, const Color& c2)
{
    Color c;
    c.R = k * c2.R;
    c.G = k * c2.G;
    c.B = k * c2.B;
    c.A = k * c2.A;
    c.correct();

    return c;
}

Color operator /(float k, const Color& c2)
{
    Color c;
    c.R = (c2.R != 0 ? k / c2.R : 1);
    c.G = (c2.G != 0 ? k / c2.G : 1);
    c.B = (c2.B != 0 ? k / c2.B : 1);
    c.A = (c2.A != 0 ? k / c2.A : 1);
    c.correct();

    return c;
}

Color operator +(const Color& c1, float k)
{
    Color c;
    c.R = c1.R + k;
    c.G = c1.G + k;
    c.B = c1.B + k;
    c.A = c1.A + k;
    c.correct();

    return c;
}

Color operator -(const Color& c1, float k)
{
    Color c;
    c.R = c1.R - k;
    c.G = c1.G - k;
    c.B = c1.B - k;
    c.A = c1.A - k;
    c.correct();

    return c;
}

Color operator *(const Color& c1, float k)
{
    Color c;
    c.R = c1.R * k;
    c.G = c1.G * k;
    c.B = c1.B * k;
    c.A = c1.A * k;
    c.correct();

    return c;
}

Color operator /(const Color& c1, float k)
{
    Color c;
    c.R = (k != 0 ? c1.R / k : 1);
    c.G = (k != 0 ? c1.G / k : 1);
    c.B = (k != 0 ? c1.B / k : 1);
    c.A = (k != 0 ? c1.A / k : 1);
    c.correct();

    return c;
}

Color Color::operator -()
{
    Color c;
    c.R = 1.0f - R;
    c.G = 1.0f - G;
    c.B = 1.0f - B;
    c.A = 1.0f - A;

    return c;
}

void ColorMap::jet(int n)
{
    if(n <= 0)
    {
        cout << "Error in \"void ColorMap::parula(int n)\"" << endl
             << "n must be positive!" << endl;
        exit(-1);
    }
    if(n_colors != n)
    {
        if(colors)
        {
            delete [] colors;
        }
        colors = new Color[n];
        n_colors = n;
    }
    if(n == 1)
    {
        colors[0] = Color(0.5f, 1.0f, 0.5f);
        return;
    }

    float x = 0, delta = 1.0f / (n - 1);
    for(int i = 0; i < n; i++)
    {
        x += delta;
        colors[i].R = exp( - 60.0f * pow(fabs(x - 0.75f), 3.2) );
        colors[i].G = exp( - 60.0f * pow(fabs(x - 0.50f), 3.2) );
        colors[i].B = exp( - 60.0f * pow(fabs(x - 0.25f), 3.2) );
    }

    is_dem = false;
}

void ColorMap::demcmap(int n)
{
    if(n <= 0)
    {
        cout << "Error in \"void ColorMap::demcmap(int n)\"" << endl
             << "n must be positive!" << endl;
        exit(-1);
    }
    if(n_colors_land != n)
    {
        if(colors_land)
        {
            delete [] colors_land;
        }
        colors_land = new Color[n];
        n_colors_land = n;
    }
    if(n_colors_sea != n)
    {
        if(colors_sea)
        {
            delete [] colors_sea;
        }
        colors_sea = new Color[n];
        n_colors_sea = n;
    }
    if(n == 1)
    {
        colors_sea[0] = Color(0.0704, 0.7457, 0.7258);
        colors_land[0] = Color(0.8964, 0.9976, 0.7950);
        return;
    }

    Matrix<float> Land = 
    {
        {0.000000f, 0.400000f, 0.200000f},
        {0.002539f, 0.404706f, 0.200468f},
        {0.005138f, 0.409412f, 0.200933f},
        {0.007795f, 0.414118f, 0.201396f},
        {0.010512f, 0.418824f, 0.201858f},
        {0.013287f, 0.423529f, 0.202320f},
        {0.016122f, 0.428235f, 0.202785f},
        {0.019015f, 0.432941f, 0.203253f},
        {0.021968f, 0.437647f, 0.203726f},
        {0.024980f, 0.442353f, 0.204205f},
        {0.028051f, 0.447059f, 0.204691f},
        {0.031181f, 0.451765f, 0.205187f},
        {0.034370f, 0.456471f, 0.205693f},
        {0.037618f, 0.461176f, 0.206211f},
        {0.040925f, 0.465882f, 0.206741f},
        {0.044291f, 0.470588f, 0.207287f},
        {0.047716f, 0.475294f, 0.207848f},
        {0.051200f, 0.480000f, 0.208427f},
        {0.054743f, 0.484706f, 0.209024f},
        {0.058346f, 0.489412f, 0.209641f},
        {0.062007f, 0.494118f, 0.210280f},
        {0.065727f, 0.498824f, 0.210942f},
        {0.069507f, 0.503529f, 0.211628f},
        {0.073345f, 0.508235f, 0.212340f},
        {0.077243f, 0.512941f, 0.213078f},
        {0.081200f, 0.517647f, 0.213845f},
        {0.085215f, 0.522353f, 0.214642f},
        {0.089290f, 0.527059f, 0.215470f},
        {0.093424f, 0.531765f, 0.216331f},
        {0.097617f, 0.536471f, 0.217226f},
        {0.101869f, 0.541176f, 0.218156f},
        {0.106179f, 0.545882f, 0.219123f},
        {0.110549f, 0.550588f, 0.220128f},
        {0.114979f, 0.555294f, 0.221172f},
        {0.119467f, 0.560000f, 0.222258f},
        {0.124014f, 0.564706f, 0.223386f},
        {0.128620f, 0.569412f, 0.224557f},
        {0.133285f, 0.574118f, 0.225774f},
        {0.138010f, 0.578824f, 0.227037f},
        {0.142793f, 0.583529f, 0.228348f},
        {0.147636f, 0.588235f, 0.229708f},
        {0.152537f, 0.592941f, 0.231119f},
        {0.157498f, 0.597647f, 0.232582f},
        {0.162517f, 0.602353f, 0.234098f},
        {0.167596f, 0.607059f, 0.235670f},
        {0.172734f, 0.611765f, 0.237297f},
        {0.177930f, 0.616471f, 0.238982f},
        {0.183186f, 0.621176f, 0.240726f},
        {0.188501f, 0.625882f, 0.242530f},
        {0.193875f, 0.630588f, 0.244397f},
        {0.199308f, 0.635294f, 0.246326f},
        {0.204800f, 0.640000f, 0.248320f},
        {0.210351f, 0.644706f, 0.250380f},
        {0.215961f, 0.649412f, 0.252507f},
        {0.221630f, 0.654118f, 0.254703f},
        {0.227359f, 0.658824f, 0.256969f},
        {0.233146f, 0.663529f, 0.259307f},
        {0.238992f, 0.668235f, 0.261717f},
        {0.244898f, 0.672941f, 0.264202f},
        {0.250862f, 0.677647f, 0.266762f},
        {0.256886f, 0.682353f, 0.269400f},
        {0.262968f, 0.687059f, 0.272115f},
        {0.269110f, 0.691765f, 0.274911f},
        {0.275311f, 0.696471f, 0.277788f},
        {0.282393f, 0.701176f, 0.281570f},
        {0.291987f, 0.705882f, 0.287889f},
        {0.301614f, 0.710588f, 0.294267f},
        {0.311272f, 0.715294f, 0.300704f},
        {0.320960f, 0.720000f, 0.307200f},
        {0.330677f, 0.724706f, 0.313755f},
        {0.340420f, 0.729412f, 0.320369f},
        {0.350190f, 0.734118f, 0.327042f},
        {0.359983f, 0.738824f, 0.333774f},
        {0.369800f, 0.743529f, 0.340566f},
        {0.379639f, 0.748235f, 0.347416f},
        {0.389497f, 0.752941f, 0.354325f},
        {0.399375f, 0.757647f, 0.361294f},
        {0.409270f, 0.762353f, 0.368321f},
        {0.419180f, 0.767059f, 0.375408f},
        {0.429106f, 0.771765f, 0.382553f},
        {0.439045f, 0.776471f, 0.389758f},
        {0.448995f, 0.781176f, 0.397021f},
        {0.458957f, 0.785882f, 0.404344f},
        {0.468927f, 0.790588f, 0.411726f},
        {0.478905f, 0.795294f, 0.419167f},
        {0.488889f, 0.800000f, 0.426667f},
        {0.498878f, 0.804706f, 0.434226f},
        {0.508871f, 0.809412f, 0.441844f},
        {0.518866f, 0.814118f, 0.449521f},
        {0.528861f, 0.818824f, 0.457257f},
        {0.538856f, 0.823529f, 0.465052f},
        {0.548849f, 0.828235f, 0.472906f},
        {0.558839f, 0.832941f, 0.480819f},
        {0.568823f, 0.837647f, 0.488792f},
        {0.578802f, 0.842353f, 0.496823f},
        {0.588773f, 0.847059f, 0.504913f},
        {0.598735f, 0.851765f, 0.513063f},
        {0.608686f, 0.856471f, 0.521272f},
        {0.618626f, 0.861176f, 0.529539f},
        {0.628553f, 0.865882f, 0.537866f},
        {0.638465f, 0.870588f, 0.546251f},
        {0.648361f, 0.875294f, 0.554696f},
        {0.658240f, 0.880000f, 0.563200f},
        {0.668100f, 0.884706f, 0.571763f},
        {0.677940f, 0.889412f, 0.580385f},
        {0.687759f, 0.894118f, 0.589066f},
        {0.697555f, 0.898824f, 0.597806f},
        {0.707326f, 0.903529f, 0.606605f},
        {0.717072f, 0.908235f, 0.615463f},
        {0.726791f, 0.912941f, 0.624380f},
        {0.736481f, 0.917647f, 0.633356f},
        {0.746142f, 0.922353f, 0.642392f},
        {0.755771f, 0.927059f, 0.651486f},
        {0.765368f, 0.931765f, 0.660639f},
        {0.774931f, 0.936471f, 0.669852f},
        {0.784458f, 0.941176f, 0.679123f},
        {0.793949f, 0.945882f, 0.688454f},
        {0.803402f, 0.950588f, 0.697844f},
        {0.812815f, 0.955294f, 0.707292f},
        {0.822187f, 0.960000f, 0.716800f},
        {0.831516f, 0.964706f, 0.726367f},
        {0.840802f, 0.969412f, 0.735993f},
        {0.850043f, 0.974118f, 0.745678f},
        {0.859238f, 0.978824f, 0.755421f},
        {0.868384f, 0.983529f, 0.765224f},
        {0.877482f, 0.988235f, 0.775087f},
        {0.886528f, 0.992941f, 0.785008f},
        {0.895523f, 0.997647f, 0.794988f},
        {0.897178f, 0.997647f, 0.794988f},
        {0.891625f, 0.992941f, 0.785008f},
        {0.886189f, 0.988235f, 0.775087f},
        {0.880869f, 0.983529f, 0.765224f},
        {0.875664f, 0.978824f, 0.755421f},
        {0.870573f, 0.974118f, 0.745678f},
        {0.865594f, 0.969412f, 0.735993f},
        {0.860725f, 0.964706f, 0.726367f},
        {0.855964f, 0.960000f, 0.716800f},
        {0.851312f, 0.955294f, 0.707292f},
        {0.846765f, 0.950588f, 0.697844f},
        {0.842322f, 0.945882f, 0.688454f},
        {0.837982f, 0.941176f, 0.679123f},
        {0.833744f, 0.936471f, 0.669852f},
        {0.829605f, 0.931765f, 0.660639f},
        {0.825565f, 0.927059f, 0.651486f},
        {0.821622f, 0.922353f, 0.642392f},
        {0.817774f, 0.917647f, 0.633356f},
        {0.814019f, 0.912941f, 0.624380f},
        {0.810357f, 0.908235f, 0.615463f},
        {0.806786f, 0.903529f, 0.606605f},
        {0.803304f, 0.898824f, 0.597806f},
        {0.799910f, 0.894118f, 0.589066f},
        {0.796603f, 0.889412f, 0.580385f},
        {0.793380f, 0.884706f, 0.571763f},
        {0.790240f, 0.880000f, 0.563200f},
        {0.787182f, 0.875294f, 0.554696f},
        {0.784204f, 0.870588f, 0.546251f},
        {0.781306f, 0.865882f, 0.537866f},
        {0.778484f, 0.861176f, 0.529539f},
        {0.775738f, 0.856471f, 0.521272f},
        {0.773066f, 0.851765f, 0.513063f},
        {0.770467f, 0.847059f, 0.504913f},
        {0.767940f, 0.842353f, 0.496823f},
        {0.765482f, 0.837647f, 0.488792f},
        {0.763092f, 0.832941f, 0.480819f},
        {0.760769f, 0.828235f, 0.472906f},
        {0.758511f, 0.823529f, 0.465052f},
        {0.756317f, 0.818824f, 0.457257f},
        {0.754186f, 0.814118f, 0.449521f},
        {0.752114f, 0.809412f, 0.441844f},
        {0.750102f, 0.804706f, 0.434226f},
        {0.748148f, 0.800000f, 0.426667f},
        {0.746250f, 0.795294f, 0.419167f},
        {0.744407f, 0.790588f, 0.411726f},
        {0.742616f, 0.785882f, 0.404344f},
        {0.740878f, 0.781176f, 0.397021f},
        {0.739189f, 0.776471f, 0.389758f},
        {0.737550f, 0.771765f, 0.382553f},
        {0.735957f, 0.767059f, 0.375408f},
        {0.734410f, 0.762353f, 0.368321f},
        {0.732907f, 0.757647f, 0.361294f},
        {0.731447f, 0.752941f, 0.354325f},
        {0.730028f, 0.748235f, 0.347416f},
        {0.728649f, 0.743529f, 0.340566f},
        {0.727307f, 0.738824f, 0.333774f},
        {0.726003f, 0.734118f, 0.327042f},
        {0.724733f, 0.729412f, 0.320369f},
        {0.723497f, 0.724706f, 0.313755f},
        {0.720000f, 0.717707f, 0.307200f},
        {0.715294f, 0.709468f, 0.300704f},
        {0.710588f, 0.701201f, 0.294267f},
        {0.705882f, 0.692905f, 0.287889f},
        {0.701176f, 0.684584f, 0.281570f},
        {0.696471f, 0.676238f, 0.275311f},
        {0.691765f, 0.667870f, 0.269110f},
        {0.687059f, 0.659479f, 0.262968f},
        {0.682353f, 0.651069f, 0.256886f},
        {0.677647f, 0.642640f, 0.250862f},
        {0.672941f, 0.634193f, 0.244898f},
        {0.668235f, 0.625732f, 0.238992f},
        {0.663529f, 0.617256f, 0.233146f},
        {0.658824f, 0.608768f, 0.227359f},
        {0.654118f, 0.600269f, 0.221630f},
        {0.649412f, 0.591760f, 0.215961f},
        {0.644706f, 0.583243f, 0.210351f},
        {0.640000f, 0.574720f, 0.204800f},
        {0.635294f, 0.566192f, 0.199308f},
        {0.630588f, 0.557660f, 0.193875f},
        {0.625882f, 0.549126f, 0.188501f},
        {0.621176f, 0.540592f, 0.183186f},
        {0.616471f, 0.532059f, 0.177930f},
        {0.611765f, 0.523528f, 0.172734f},
        {0.607059f, 0.515001f, 0.167596f},
        {0.602353f, 0.506480f, 0.162517f},
        {0.597647f, 0.497966f, 0.157498f},
        {0.592941f, 0.489461f, 0.152537f},
        {0.588235f, 0.480965f, 0.147636f},
        {0.583529f, 0.472481f, 0.142793f},
        {0.578824f, 0.464010f, 0.138010f},
        {0.574118f, 0.455554f, 0.133285f},
        {0.569412f, 0.447114f, 0.128620f},
        {0.564706f, 0.438691f, 0.124014f},
        {0.560000f, 0.430287f, 0.119467f},
        {0.555294f, 0.421904f, 0.114979f},
        {0.550588f, 0.413543f, 0.110549f},
        {0.545882f, 0.405206f, 0.106179f},
        {0.541176f, 0.396894f, 0.101869f},
        {0.536471f, 0.388608f, 0.097617f},
        {0.531765f, 0.380351f, 0.093424f},
        {0.527059f, 0.372123f, 0.089290f},
        {0.522353f, 0.363926f, 0.085215f},
        {0.517647f, 0.355762f, 0.081200f},
        {0.512941f, 0.347632f, 0.077243f},
        {0.508235f, 0.339538f, 0.073345f},
        {0.503529f, 0.331481f, 0.069507f},
        {0.498824f, 0.323462f, 0.065727f},
        {0.494118f, 0.315484f, 0.062007f},
        {0.489412f, 0.307547f, 0.058346f},
        {0.484706f, 0.299653f, 0.054743f},
        {0.480000f, 0.291804f, 0.051200f},
        {0.475294f, 0.284002f, 0.047716f},
        {0.470588f, 0.276247f, 0.044291f},
        {0.465882f, 0.268541f, 0.040925f},
        {0.461176f, 0.260886f, 0.037618f},
        {0.456471f, 0.253283f, 0.034370f},
        {0.451765f, 0.245733f, 0.031181f},
        {0.447059f, 0.238239f, 0.028051f},
        {0.442353f, 0.230802f, 0.024980f},
        {0.437647f, 0.223423f, 0.021968f},
        {0.432941f, 0.216104f, 0.019015f},
        {0.428235f, 0.208845f, 0.016122f},
        {0.423529f, 0.201650f, 0.013287f},
        {0.418824f, 0.194519f, 0.010512f},
        {0.414118f, 0.187453f, 0.007795f},
        {0.409412f, 0.180455f, 0.005138f},
        {0.404706f, 0.173526f, 0.002539f},
        {0.400000f, 0.166667f, 0.000000f},
    };
    int N_land = Land.rows();

    for(int i = 0; i < n_colors_land; i++)
    {
        float x = 1.0f * i / (n_colors_land-1) * (N_land - 1);
        int row = floor(x);
        float rear = x- row;
        if(rear >= 0.001f)
        {
            colors_land[i].R = (1.0f - rear) * Land(row, 0) + rear * Land(row + 1, 0);
            colors_land[i].G = (1.0f - rear) * Land(row, 1) + rear * Land(row + 1, 1);
            colors_land[i].B = (1.0f - rear) * Land(row, 2) + rear * Land(row + 1, 2);
        }
        else
        {
            colors_land[i].R = Land(row, 0);
            colors_land[i].G = Land(row, 1);
            colors_land[i].B = Land(row, 2);
        }
    }

    float r_start = 4.0f/255;
    float r_end = 30.0f/255;
    float g_start = 29.0f/255;
    float g_end = 123.0f/255;
    float b_start = 85.0f/255;
    float b_end = 192.0f/255;
    for(int i = 0; i < n_colors_sea; i++)
    {
        float x = 1.0f * i / (n_colors_land-1);
        x = 0.3f * x * x + 0.7f * x;
        
        colors_sea[i].R = (r_end-r_start)/2*(sin(PI*x-PI/2)+1)+r_start;
        colors_sea[i].G = (g_end-g_start)/2*(sin(PI*x-PI/2)+1)+g_start;
        colors_sea[i].B = (b_end-b_start)/2*(sin(PI*x-PI/2)+1)+b_start;
    }

    is_dem = true;
}

void ColorMap::parula(int n)
{
    if(n <= 0)
    {
        cout << "Error in \"void ColorMap::parula(int n)\"" << endl
             << "n must be positive!" << endl;
        exit(-1);
    }
    if(n_colors != n)
    {
        if(colors)
        {
            delete [] colors;
        }
        colors = new Color[n];
        n_colors = n;
    }
    if(n == 1)
    {
        colors[0] = Color(0.0704, 0.7457, 0.7258);
        return;
    }

    Matrix<float> C = 
    {
        {0.2081f, 0.1663f, 0.5292f},
        {0.2091f, 0.1721f, 0.5411f},
        {0.2101f, 0.1779f, 0.5530f},
        {0.2109f, 0.1837f, 0.5650f},
        {0.2116f, 0.1895f, 0.5771f},
        {0.2121f, 0.1954f, 0.5892f},
        {0.2124f, 0.2013f, 0.6013f},
        {0.2125f, 0.2072f, 0.6135f},
        {0.2123f, 0.2132f, 0.6258f},
        {0.2118f, 0.2192f, 0.6381f},
        {0.2111f, 0.2253f, 0.6505f},
        {0.2099f, 0.2315f, 0.6629f},
        {0.2084f, 0.2377f, 0.6753f},
        {0.2063f, 0.2440f, 0.6878f},
        {0.2038f, 0.2503f, 0.7003f},
        {0.2006f, 0.2568f, 0.7129f},
        {0.1968f, 0.2632f, 0.7255f},
        {0.1921f, 0.2698f, 0.7381f},
        {0.1867f, 0.2764f, 0.7507f},
        {0.1802f, 0.2832f, 0.7634f},
        {0.1728f, 0.2902f, 0.7762f},
        {0.1641f, 0.2975f, 0.7890f},
        {0.1541f, 0.3052f, 0.8017f},
        {0.1427f, 0.3132f, 0.8145f},
        {0.1295f, 0.3217f, 0.8269f},
        {0.1147f, 0.3306f, 0.8387f},
        {0.0986f, 0.3397f, 0.8495f},
        {0.0816f, 0.3486f, 0.8588f},
        {0.0646f, 0.3572f, 0.8664f},
        {0.0482f, 0.3651f, 0.8722f},
        {0.0329f, 0.3724f, 0.8765f},
        {0.0213f, 0.3792f, 0.8796f},
        {0.0136f, 0.3853f, 0.8815f},
        {0.0086f, 0.3911f, 0.8827f},
        {0.0060f, 0.3965f, 0.8833f},
        {0.0051f, 0.4017f, 0.8834f},
        {0.0054f, 0.4066f, 0.8831f},
        {0.0067f, 0.4113f, 0.8825f},
        {0.0089f, 0.4159f, 0.8816f},
        {0.0116f, 0.4203f, 0.8805f},
        {0.0148f, 0.4246f, 0.8793f},
        {0.0184f, 0.4288f, 0.8779f},
        {0.0223f, 0.4329f, 0.8763f},
        {0.0264f, 0.4370f, 0.8747f},
        {0.0306f, 0.4410f, 0.8729f},
        {0.0349f, 0.4449f, 0.8711f},
        {0.0394f, 0.4488f, 0.8692f},
        {0.0437f, 0.4526f, 0.8672f},
        {0.0477f, 0.4564f, 0.8652f},
        {0.0514f, 0.4602f, 0.8632f},
        {0.0549f, 0.4640f, 0.8611f},
        {0.0582f, 0.4677f, 0.8589f},
        {0.0612f, 0.4714f, 0.8568f},
        {0.0640f, 0.4751f, 0.8546f},
        {0.0666f, 0.4788f, 0.8525f},
        {0.0689f, 0.4825f, 0.8503f},
        {0.0710f, 0.4862f, 0.8481f},
        {0.0729f, 0.4899f, 0.8460f},
        {0.0746f, 0.4937f, 0.8439f},
        {0.0761f, 0.4974f, 0.8418f},
        {0.0773f, 0.5012f, 0.8398f},
        {0.0782f, 0.5051f, 0.8378f},
        {0.0789f, 0.5089f, 0.8359f},
        {0.0794f, 0.5129f, 0.8341f},
        {0.0795f, 0.5169f, 0.8324f},
        {0.0793f, 0.5210f, 0.8308f},
        {0.0788f, 0.5251f, 0.8293f},
        {0.0778f, 0.5295f, 0.8280f},
        {0.0764f, 0.5339f, 0.8270f},
        {0.0746f, 0.5384f, 0.8261f},
        {0.0724f, 0.5431f, 0.8253f},
        {0.0698f, 0.5479f, 0.8247f},
        {0.0668f, 0.5527f, 0.8243f},
        {0.0636f, 0.5577f, 0.8239f},
        {0.0600f, 0.5627f, 0.8237f},
        {0.0562f, 0.5677f, 0.8234f},
        {0.0523f, 0.5727f, 0.8231f},
        {0.0484f, 0.5777f, 0.8228f},
        {0.0445f, 0.5826f, 0.8223f},
        {0.0408f, 0.5874f, 0.8217f},
        {0.0372f, 0.5922f, 0.8209f},
        {0.0342f, 0.5968f, 0.8198f},
        {0.0317f, 0.6012f, 0.8186f},
        {0.0296f, 0.6055f, 0.8171f},
        {0.0279f, 0.6097f, 0.8154f},
        {0.0265f, 0.6137f, 0.8135f},
        {0.0255f, 0.6176f, 0.8114f},
        {0.0248f, 0.6214f, 0.8091f},
        {0.0243f, 0.6250f, 0.8066f},
        {0.0239f, 0.6285f, 0.8039f},
        {0.0237f, 0.6319f, 0.8010f},
        {0.0235f, 0.6352f, 0.7980f},
        {0.0233f, 0.6384f, 0.7948f},
        {0.0231f, 0.6415f, 0.7916f},
        {0.0230f, 0.6445f, 0.7881f},
        {0.0229f, 0.6474f, 0.7846f},
        {0.0227f, 0.6503f, 0.7810f},
        {0.0227f, 0.6531f, 0.7773f},
        {0.0232f, 0.6558f, 0.7735f},
        {0.0238f, 0.6585f, 0.7696f},
        {0.0246f, 0.6611f, 0.7656f},
        {0.0263f, 0.6637f, 0.7615f},
        {0.0282f, 0.6663f, 0.7574f},
        {0.0306f, 0.6688f, 0.7532f},
        {0.0338f, 0.6712f, 0.7490f},
        {0.0373f, 0.6737f, 0.7446f},
        {0.0418f, 0.6761f, 0.7402f},
        {0.0467f, 0.6784f, 0.7358f},
        {0.0516f, 0.6808f, 0.7313f},
        {0.0574f, 0.6831f, 0.7267f},
        {0.0629f, 0.6854f, 0.7221f},
        {0.0692f, 0.6877f, 0.7173f},
        {0.0755f, 0.6899f, 0.7126f},
        {0.0820f, 0.6921f, 0.7078f},
        {0.0889f, 0.6943f, 0.7029f},
        {0.0956f, 0.6965f, 0.6979f},
        {0.1031f, 0.6986f, 0.6929f},
        {0.1104f, 0.7007f, 0.6878f},
        {0.1180f, 0.7028f, 0.6827f},
        {0.1258f, 0.7049f, 0.6775f},
        {0.1335f, 0.7069f, 0.6723f},
        {0.1418f, 0.7089f, 0.6669f},
        {0.1499f, 0.7109f, 0.6616f},
        {0.1585f, 0.7129f, 0.6561f},
        {0.1671f, 0.7148f, 0.6507f},
        {0.1758f, 0.7168f, 0.6451f},
        {0.1849f, 0.7186f, 0.6395f},
        {0.1938f, 0.7205f, 0.6338f},
        {0.2033f, 0.7223f, 0.6281f},
        {0.2128f, 0.7241f, 0.6223f},
        {0.2224f, 0.7259f, 0.6165f},
        {0.2324f, 0.7275f, 0.6107f},
        {0.2423f, 0.7292f, 0.6048f},
        {0.2527f, 0.7308f, 0.5988f},
        {0.2631f, 0.7324f, 0.5929f},
        {0.2735f, 0.7339f, 0.5869f},
        {0.2845f, 0.7354f, 0.5809f},
        {0.2953f, 0.7368f, 0.5749f},
        {0.3064f, 0.7381f, 0.5689f},
        {0.3177f, 0.7394f, 0.5630f},
        {0.3289f, 0.7406f, 0.5570f},
        {0.3405f, 0.7417f, 0.5512f},
        {0.3520f, 0.7428f, 0.5453f},
        {0.3635f, 0.7438f, 0.5396f},
        {0.3753f, 0.7446f, 0.5339f},
        {0.3869f, 0.7454f, 0.5283f},
        {0.3986f, 0.7461f, 0.5229f},
        {0.4103f, 0.7467f, 0.5175f},
        {0.4218f, 0.7473f, 0.5123f},
        {0.4334f, 0.7477f, 0.5072f},
        {0.4447f, 0.7482f, 0.5021f},
        {0.4561f, 0.7485f, 0.4972f},
        {0.4672f, 0.7487f, 0.4924f},
        {0.4783f, 0.7489f, 0.4877f},
        {0.4892f, 0.7491f, 0.4831f},
        {0.5000f, 0.7491f, 0.4786f},
        {0.5106f, 0.7492f, 0.4741f},
        {0.5212f, 0.7492f, 0.4698f},
        {0.5315f, 0.7491f, 0.4655f},
        {0.5418f, 0.7490f, 0.4613f},
        {0.5519f, 0.7489f, 0.4571f},
        {0.5619f, 0.7487f, 0.4531f},
        {0.5718f, 0.7485f, 0.4490f},
        {0.5816f, 0.7482f, 0.4451f},
        {0.5913f, 0.7479f, 0.4412f},
        {0.6009f, 0.7476f, 0.4374f},
        {0.6103f, 0.7473f, 0.4335f},
        {0.6197f, 0.7469f, 0.4298f},
        {0.6290f, 0.7465f, 0.4261f},
        {0.6382f, 0.7460f, 0.4224f},
        {0.6473f, 0.7456f, 0.4188f},
        {0.6564f, 0.7451f, 0.4152f},
        {0.6653f, 0.7446f, 0.4116f},
        {0.6742f, 0.7441f, 0.4081f},
        {0.6830f, 0.7435f, 0.4046f},
        {0.6918f, 0.7430f, 0.4011f},
        {0.7004f, 0.7424f, 0.3976f},
        {0.7091f, 0.7418f, 0.3942f},
        {0.7176f, 0.7412f, 0.3908f},
        {0.7261f, 0.7405f, 0.3874f},
        {0.7346f, 0.7399f, 0.3840f},
        {0.7430f, 0.7392f, 0.3806f},
        {0.7513f, 0.7385f, 0.3773f},
        {0.7596f, 0.7378f, 0.3739f},
        {0.7679f, 0.7372f, 0.3706f},
        {0.7761f, 0.7364f, 0.3673f},
        {0.7843f, 0.7357f, 0.3639f},
        {0.7924f, 0.7350f, 0.3606f},
        {0.8005f, 0.7343f, 0.3573f},
        {0.8085f, 0.7336f, 0.3539f},
        {0.8166f, 0.7329f, 0.3506f},
        {0.8246f, 0.7322f, 0.3472f},
        {0.8325f, 0.7315f, 0.3438f},
        {0.8405f, 0.7308f, 0.3404f},
        {0.8484f, 0.7301f, 0.3370f},
        {0.8563f, 0.7294f, 0.3336f},
        {0.8642f, 0.7288f, 0.3300f},
        {0.8720f, 0.7282f, 0.3265f},
        {0.8798f, 0.7276f, 0.3229f},
        {0.8877f, 0.7271f, 0.3193f},
        {0.8954f, 0.7266f, 0.3156f},
        {0.9032f, 0.7262f, 0.3117f},
        {0.9110f, 0.7259f, 0.3078f},
        {0.9187f, 0.7256f, 0.3038f},
        {0.9264f, 0.7256f, 0.2996f},
        {0.9341f, 0.7256f, 0.2953f},
        {0.9417f, 0.7259f, 0.2907f},
        {0.9493f, 0.7264f, 0.2859f},
        {0.9567f, 0.7273f, 0.2808f},
        {0.9639f, 0.7285f, 0.2754f},
        {0.9708f, 0.7303f, 0.2696f},
        {0.9773f, 0.7326f, 0.2634f},
        {0.9831f, 0.7355f, 0.2570f},
        {0.9882f, 0.7390f, 0.2504f},
        {0.9922f, 0.7431f, 0.2437f},
        {0.9952f, 0.7476f, 0.2373f},
        {0.9973f, 0.7524f, 0.2310f},
        {0.9986f, 0.7573f, 0.2251f},
        {0.9991f, 0.7624f, 0.2195f},
        {0.9990f, 0.7675f, 0.2141f},
        {0.9985f, 0.7726f, 0.2090f},
        {0.9976f, 0.7778f, 0.2042f},
        {0.9964f, 0.7829f, 0.1995f},
        {0.9950f, 0.7880f, 0.1949f},
        {0.9933f, 0.7931f, 0.1905f},
        {0.9914f, 0.7981f, 0.1863f},
        {0.9894f, 0.8032f, 0.1821f},
        {0.9873f, 0.8083f, 0.1780f},
        {0.9851f, 0.8133f, 0.1740f},
        {0.9828f, 0.8184f, 0.1700f},
        {0.9805f, 0.8235f, 0.1661f},
        {0.9782f, 0.8286f, 0.1622f},
        {0.9759f, 0.8337f, 0.1583f},
        {0.9736f, 0.8389f, 0.1544f},
        {0.9713f, 0.8441f, 0.1505f},
        {0.9692f, 0.8494f, 0.1465f},
        {0.9672f, 0.8548f, 0.1425f},
        {0.9654f, 0.8603f, 0.1385f},
        {0.9638f, 0.8659f, 0.1343f},
        {0.9623f, 0.8716f, 0.1301f},
        {0.9611f, 0.8774f, 0.1258f},
        {0.9600f, 0.8834f, 0.1215f},
        {0.9593f, 0.8895f, 0.1171f},
        {0.9588f, 0.8958f, 0.1126f},
        {0.9586f, 0.9022f, 0.1082f},
        {0.9587f, 0.9088f, 0.1036f},
        {0.9591f, 0.9155f, 0.0990f},
        {0.9599f, 0.9225f, 0.0944f},
        {0.9610f, 0.9296f, 0.0897f},
        {0.9624f, 0.9368f, 0.0850f},
        {0.9641f, 0.9443f, 0.0802f},
        {0.9662f, 0.9518f, 0.0753f},
        {0.9685f, 0.9595f, 0.0703f},
        {0.9710f, 0.9673f, 0.0651f},
        {0.9736f, 0.9752f, 0.0597f},
        {0.9763f, 0.9831f, 0.0538f}
    };
    int N = C.rows();
    float x = 0;
    for(int i = 0; i < n; i++)
    {
        x = 1.0f*i/(n-1)*(N-1);
        int row = floor(x);
        float rear = x - row;
        if(rear >= 0.01f)
        {
            colors[i].R = (1.0f - rear) * C(row, 0) + rear * C(row + 1, 0);
            colors[i].G = (1.0f - rear) * C(row, 1) + rear * C(row + 1, 1);
            colors[i].B = (1.0f - rear) * C(row, 2) + rear * C(row + 1, 2);
        }
        else
        {
            colors[i].R = C(row, 0);
            colors[i].G = C(row, 1);
            colors[i].B = C(row, 2);
        }
    }
    is_dem = false;
}

Color ColorMap::getColor(float value)
{
    if(value > max_value || value < min_value)
    {
        cout << "Error using 'Color ColorMap::getColor(float value)'," << endl
             << "value is out of bande now!" << endl;
        exit(-1);
    }

    if(!is_dem)
    {
        float x = (max_value != min_value ? (value - min_value) / (max_value - min_value) : 0.5f) * (n_colors - 1);
        int row = floor(x);
        float rear = x - row;

        return rear != 0 ? (1.0f - rear) * colors[row] + rear * colors[row+1] : colors[row];
    }
    else
    {
        if(value < 0)
        {
            float x = (value - min_value)/(-min_value) * (n_colors_sea - 1);
            int row = floor(x);
            float rear = x-row;

            return rear != 0 ? (1.0f - rear) * colors_sea[row] + rear * colors_sea[row+1] : colors_sea[row];
        }
        else
        {
            float x = (max_value != 0 ? value / max_value : 0) * (n_colors_land - 1);
            int row = floor(x);
            float rear = x-row;

            return rear != 0 ? (1.0f - rear) * colors_land[row] + rear * colors_land[row+1] : colors_land[row];
        }
    }
}

Matrix<Color> ColorMap::getColor(const Matrix<float>& V)
{
    float min = V.min();
    float max = V.max();
    int n = V.size();

    if(is_dem)
    {
        if(min == max)
        {
            if(min < 0)
            {
                return Matrix<Color>(V.rows(), V.cols(), colors_sea[n_colors_sea-1]);
            }
            else
            {
                return Matrix<Color>(V.rows(), V.cols(), colors_land[0]);
            }
        }

        Matrix<Color> C(V.rows(), V.cols());
        for(int i = 0; i < n; i++)
        {
            if(V(i) < 0)
            {
                float x = (V(i) - min)/(-min) * (n_colors_sea - 1);
                int row = floor(x);
                float rear = x-row;

                C(i) = (rear != 0 ? (1.0f - rear) * colors_sea[row] + rear * colors_sea[row+1] : colors_sea[row]);
            }
            else
            {
                float x = (max != 0 ? V(i) / max : 0) * (n_colors_land - 1);
                int row = floor(x);
                float rear = x-row;

                C(i) = (rear != 0 ? (1.0f - rear) * colors_land[row] + rear * colors_land[row+1] : colors_land[row]);
            }
        }
        return C;
    }
    else
    {
        if(min == max)
        {
            float half = n_colors/2.0f;
            if(floor(half) == half)
            {
                return Matrix<Color>(V.rows(), V.cols(), (colors[(int)(half-1)] + colors[(int)half])/2);
            }
            else
            {
                return Matrix<Color>(V.rows(), V.cols(), colors[(int)half]);
            }
        }

        Matrix<Color> C(V.rows(), V.cols());
        for(int i = 0; i < n; i++)
        {
            float x = (V(i) - min) / (max - min) * (n_colors - 1);
            int row = floor(x);
            float rear = x - row;
            C(i) = (rear != 0 ? (1.0f - rear) * colors[row] + rear * colors[row+1] : colors[row]);
        }
        return C;
    }
}

void ColorMap::set_min(float min)
{
    min_value = min;
}

void ColorMap::set_max(float max)
{
    max_value = max;
}

void ColorMap::set_minmax(float min, float max)
{
    min_value = min;
    max_value = max;
}

void splitRGBA(const Matrix<Color>& C, Matrix<float>& R, Matrix<float>& G, Matrix<float>& B, Matrix<float>& A)
{
    int n = C.size();
    for(int i = 0; i < n; i++)
    {
        R(i) = C(i).R;
        G(i) = C(i).G;
        B(i) = C(i).B;
        A(i) = C(i).A;
    }
}