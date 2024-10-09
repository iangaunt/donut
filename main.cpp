#include <cmath>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
    string lum_chars = ".,-~:;=!*#$@";

    const int width = 40;
    const int height = 40;

    const float theta_spacing = 0.07;
    const float phi_spacing = 0.02;

    const float r1 = 1;
    const float r2 = 2;
    const float k2 = 5;

    const float k1 = width * k2 * 3 / (8 * (r1 + r2));

    float a = 1;
    float b = 1;

    int frames = 0;
    while (true) {
        std::system("cls");

        float cos_a = cos(a);
        float sin_a = sin(a);

        float cos_b = cos(b);
        float sin_b = sin(b);

        char output[width][height];
        float z_buffer[width][height];

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                output[i][j] = ' ';
                z_buffer[i][j] = 0.0;
            }   
        }

        for (float theta = 0; theta < 2 * 3.1415926; theta += theta_spacing) {
            float cos_theta = cos(theta);
            float sin_theta = sin(theta);

            for (float phi = 0; phi < 2 * 3.1415926; phi += phi_spacing) {
                float cos_phi = cos(phi);
                float sin_phi = sin(phi);

                float c_x = r2 + r1 * cos_theta;
                float c_y = r1 * sin_theta;

                float x = c_x * (cos_b * cos_phi + sin_a * sin_b * sin_phi) - c_y * cos_a * sin_b;
                float y = c_x * (sin_b * cos_phi - sin_a * cos_b * sin_phi) + c_y * cos_a * cos_b;
                float z = k2 + cos_a * c_x * sin_phi + c_y * sin_a;
                float z_frac = 1 / z;

                int xp = (int) (width / 2 + k1 * z_frac * x);
                int yp = (int) (height / 2 - k1 * z_frac * y);

                float l = cos_phi * cos_theta * sin_b - 
                    cos_a * cos_theta * sin_phi - 
                    sin_a * sin_theta + cos_b * 
                    (cos_a * sin_theta - cos_theta * sin_a * sin_phi); 

                if (l > 0) {
                    if (z_frac > z_buffer[xp][yp]) {
                        z_buffer[xp][yp] = z_frac;
                        int lum_index = l * 8;
                        output[xp][yp] = lum_chars[lum_index];
                    }
                }
            }
        }   

        frames++;

        for (int i = 0; i < width; i++) {
            string row = "";
            for (int j = 0; j < height; j++) {
                row += output[i][j];
            }
            cout << row << endl;
        }

        a += 0.07f;
        b += 0.03f;
    }
}