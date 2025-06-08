#include <stdio.h>
#include <math.h>

// Konstanta gas ideal
const double R = 0.08206; // L*atm/(mol*K)

// Fungsi f(V) = (RT / (V - b)) - (a / V^2) - P
double f(double V, double P, double T, double a, double b) {
    return (R * T / (V - b)) - (a / (V * V)) - P;
}

// Turunan pertama f(V) terhadap V: f'(V) = -RT / (V - b)^2 + 2a / V^3
double df(double V, double P, double T, double a, double b) {
    return -R * T / pow((V - b), 2) + 2 * a / pow(V, 3);
}

int main() {
    // Parameter input
    double P_atm = 1.0;   // Tekanan (atm)
    double T_K = 300.0;   // Suhu (K)
    double a = 16.26;     // Konstanta Van der Waals untuk n-butana (L^2*atm/mol^2)
    double b = 0.1132;    // Konstanta Van der Waals untuk n-butana (L/mol)
    double V_initial = 22.4; // Tebakan awal untuk volume (L/mol), bisa volume gas ideal

    // Kriteria konvergensi
    double tolerance = 1e-6; // Toleransi error
    int max_iterations = 100; // Iterasi maksimum

    printf("Simulasi Persamaan Keadaan Van der Waals menggunakan Metode Newton-Raphson\n");
    printf("-----------------------------------------------------------------------\n");
    printf("Parameter Input:\n");
    printf("Tekanan (P)     : %.2f atm\n", P_atm);
    printf("Suhu (T)        : %.2f K\n", T_K);
    printf("Konstanta a     : %.4f L^2*atm/mol^2\n", a);
    printf("Konstanta b     : %.4f L/mol\n", b);
    printf("Tebakan Awal V  : %.4f L/mol\n", V_initial);
    printf("Toleransi       : %.0e\n", tolerance);
    printf("Max Iterasi     : %d\n\n", max_iterations);

    double V_current = V_initial;
    double V_next;
    int iteration = 0;
    double error = 1.0; // Inisialisasi error besar agar loop berjalan

    printf("Iterasi | V (L/mol)      | f(V)           | f'(V)          | Error (abs(V_next - V_current))\n");
    printf("--------|----------------|----------------|----------------|----------------------------------\n");

    while (error > tolerance && iteration < max_iterations) {
        double f_val = f(V_current, P_atm, T_K, a, b);
        double df_val = df(V_current, P_atm, T_K, a, b);

        // Hindari pembagian dengan nol atau nilai turunan yang sangat kecil
        if (fabs(df_val) < 1e-10) {
            fprintf(stderr, "Error: Turunan sangat mendekati nol. Metode Newton-Raphson mungkin tidak konvergen atau tebakan awal buruk.\n");
            return 1;
        }

        V_next = V_current - f_val / df_val;
        error = fabs(V_next - V_current);

        printf("%7d | %14.8f | %14.8f | %14.8f | %32.8e\n",
               iteration, V_current, f_val, df_val, error);

        V_current = V_next;
        iteration++;
    }

    printf("\n-----------------------------------------------------------------------\n");
    if (error <= tolerance) {
        printf("Konvergen setelah %d iterasi.\n", iteration);
        printf("Volume molar (V) = %.8f L/mol\n", V_current);
    } else {
        printf("Tidak konvergen setelah %d iterasi.\n", max_iterations);
        printf("Volume molar terakhir (V) = %.8f L/mol\n", V_current);
    }

    return 0;
}


