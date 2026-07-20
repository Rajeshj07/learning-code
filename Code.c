#include <stdio.h>

// Helper function to calculate the Greatest Common Divisor (GCD)
long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

long long nextTogether(int a, int b) {
    // Cast to long long first to prevent overflow during multiplication!
    long long numA = a;
    long long numB = b;
    
    // LCM formula: (A * B) / GCD(A, B)
    long long lcm = (numA * numB) / gcd(numA, numB);
    
    return lcm;
}

int main() {
    int a, b;

    // Read two integers from input
    if (scanf("%d %d", &a, &b) != 2) {
        return 1; // Basic safety check for input
    }

    // Call the logic function and print the result
    long long result = nextTogether(a, b);
    printf("%lld\n", result);

    return 0;
}
