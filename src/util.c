#include "headers/util.h"

FILE *input_file(char *run_name) {
    char *file_path = malloc((strlen(run_name) + 11 + 1) * sizeof(char));
    sprintf(file_path, "inputs/%s.txt", run_name);
    FILE *res = fopen(file_path, "r");
    if (res == NULL) {
        perror("Error opening input file");
        exit(1);
    }
    free(file_path);
    return res;
}

FILE *output_file(char *run_name) {
    char *file_path = malloc((strlen(run_name) + 12 + 1) * sizeof(char));
    sprintf(file_path, "outputs/%s.xyz", run_name);
    FILE *res = fopen(file_path, "w");
    if (res == NULL) {
        perror("Error opening output file");
        exit(1);
    }
    free(file_path);
    return res;
}

// Requires input file to be formatted exactly as 10.txt is
int num_lines(char *run_name) {
    FILE *file = input_file(run_name);

    int res = 0;
    double temp;
    while (fscanf(file, "%lf", &temp) > 0) res++;

    fclose(file);
    return res / 3;
}

/* Distance from p1 to nearest image of p2 */
dis_t calc_nearest_distance(pos_t p1, pos_t p2) {
    double x = p2.x - p1.x;
    if (x < -(sidelen / 2)) x += sidelen;
    else if (x > sidelen / 2) x -= sidelen;
    double y = p2.y - p1.y;
    if (y < -(sidelen / 2)) y += sidelen;
    else if (y > sidelen / 2) y -= sidelen;
    double z = p2.z - p1.z;
    if (z < -(sidelen / 2)) z += sidelen;
    else if (z > sidelen / 2) z -= sidelen;

    double agg = sqrt(x * x + y * y + z * z);
    return (dis_t) { .x = x, .y = y, .z = z, .agg = agg };
}

/* LJ force on particle a, where particle b is at distance `distance` */
frc_t calc_force(dis_t distance) {
    if (distance.agg > cutoff) return (frc_t) { .x = 0, .y = 0, .z = 0 };
    double force = 48.0 / pow(distance.agg, 13.0) - 24.0 / pow(distance.agg, 7.0) + fcut;
    double fx = force * (distance.x / distance.agg);
    double fy = force * (distance.y / distance.agg);
    double fz = force * (distance.z / distance.agg);

    // Have to negate because above calculates force ON something distance `distance` away, but we want force FROM that
    return (frc_t) { .x = -fx, .y = -fy, .z = -fz };
}

/* Approximation of the inverse cdf of Norm(0, 1)
 * Taken from `https://web.archive.org/web/20151110174102/http://home.online.no/~pjacklam/notes/invnorm#The_distribution_function` */
double invnormcdf(double p) {
    double a1 = -3.969683028665376e+01;
    double a2 = 2.209460984245205e+02;
    double a3 = -2.759285104469687e+02;
    double a4 = 1.383577518672690e+02;
    double a5 = -3.066479806614716e+01;
    double a6 = 2.506628277459239e+00;

    double b1 = -5.447609879822406e+01;
    double b2 = 1.615858368580409e+02;
    double b3 = -1.556989798598866e+02;
    double b4 = 6.680131188771972e+01;
    double b5 = -1.328068155288572e+01;

    double c1 = -7.784894002430293e-03;
    double c2 = -3.223964580411365e-01;
    double c3 = -2.400758277161838e+00;
    double c4 = -2.549732539343734e+00;
    double c5 = 4.374664141464968e+00;
    double c6 = 2.938163982698783e+00;

    double d1 = 7.784695709041462e-03;
    double d2 = 3.224671290700398e-01;
    double d3 = 2.445134137142996e+00;
    double d4 = 3.754408661907416e+00;

    double plow = 0.02425;
    double phi = 1 - plow;

    if (p < plow) {
        double q = sqrt(-2 * log(p));
        return (((((c1 * q + c2) * q + c3) * q + c4) * q + c5) * q + c6) / ((((d1 * q + d2) * q + d3) * q + d4) * q + 1);
    } else if (p <= phi) {
        double q = p - 0.5;
        double r = q * q;
        return (((((a1 * r + a2) * r + a3) * r + a4) * r + a5) * r + a6) * q / (((((b1 * r + b2) * r + b3) * r + b4) * r + b5) * r + 1);
    } else {
        double q = sqrt(-2 * log(1 - p));
        return -(((((c1 * q + c2) * q + c3) * q + c4) * q + c5) * q + c6) / ((((d1 * q + d2) * q + d3) * q + d4) * q + 1);
    }
}

/* Samples from Norm(mean, stdev^2) */
double rnorm(double mean, double stdev) {
    double p = ((double) rand()) / ((double) (RAND_MAX / 1.0L));
    return mean + stdev * invnormcdf(p);
}
