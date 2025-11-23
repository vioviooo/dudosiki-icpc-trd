#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <climits>

int binary_search(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2; // Prevents overflow
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Target not found
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    int target = 7;
    
    int index = binary_search(arr, target);
    if (index != -1) {
        cout << "Found at index: " << index << endl;
    } else {
        cout << "Not found" << endl;
    }
    
    auto it = lower_bound(arr.begin(), arr.end(), target);
    if (it != arr.end() && *it == target) {
        cout << "Found at index: " << (it - arr.begin()) << endl;
    } else {
        cout << "Not found" << endl;
    }
    
    return 0;
}

// Check if element exists
bool exists = binary_search(arr.begin(), arr.end(), target);

// Find first element >= target
auto lb = lower_bound(arr.begin(), arr.end(), target);

// Find first element > target  
auto ub = upper_bound(arr.begin(), arr.end(), target);

// Count occurrences of target
int count = ub - lb;

class BaseConverter {
public:
    // Convert a number string from one base to another
    static std::string convertBase(const std::string& number, 
                                  int fromBase, 
                                  int toBase) {
        validateBases(fromBase, toBase);
        
        if (number.empty()) {
            throw std::invalid_argument("Empty number string");
        }
        
        // Handle special case: same base
        if (fromBase == toBase) {
            return number;
        }
        
        // Convert to decimal first, then to target base
        long long decimalValue = toDecimal(number, fromBase);
        return fromDecimal(decimalValue, toBase);
    }
    
    // Convert floating point numbers between bases
    static std::string convertFloat(const std::string& number,
                                   int fromBase,
                                   int toBase,
                                   int precision = 10) {
        validateBases(fromBase, toBase);
        
        if (precision <= 0) {
            throw std::invalid_argument("Precision must be positive");
        }
        
        // Split into integer and fractional parts
        size_t decimalPos = number.find('.');
        std::string integerPart, fractionalPart;
        
        if (decimalPos == std::string::npos) {
            integerPart = number;
            fractionalPart = "";
        } else {
            integerPart = number.substr(0, decimalPos);
            fractionalPart = number.substr(decimalPos + 1);
        }
        
        // Convert integer part
        std::string resultInteger = convertBase(integerPart, fromBase, toBase);
        
        // Convert fractional part if it exists
        if (fractionalPart.empty()) {
            return resultInteger;
        }
        
        std::string resultFractional = convertFractionalPart(fractionalPart, fromBase, toBase, precision);
        
        return resultInteger + "." + resultFractional;
    }
    
    // Utility function to check if a string is valid for a given base
    static bool isValidForBase(const std::string& number, int base) {
        if (number.empty()) return false;
        
        try {
            size_t startIndex = 0;
            
            // Check for sign
            if (number[0] == '+' || number[0] == '-') {
                startIndex = 1;
                if (number.length() == 1) return false; // Just a sign is invalid
            }
            
            // Check for decimal point in integer conversion
            if (number.find('.') != std::string::npos) {
                return false;
            }
            
            // Check each character
            for (size_t i = startIndex; i < number.length(); i++) {
                char c = number[i];
                int digit = charToDigit(c);
                if (digit >= base) {
                    return false;
                }
            }
            
            return true;
        } catch (...) {
            return false;
        }
    }

private:
    static void validateBases(int fromBase, int toBase) {
        if (fromBase < 2 || fromBase > 36) {
            throw std::invalid_argument("Source base must be between 2 and 36");
        }
        if (toBase < 2 || toBase > 36) {
            throw std::invalid_argument("Target base must be between 2 and 36");
        }
    }
    
    // Convert from any base to decimal
    static long long toDecimal(const std::string& number, int base) {
        long long result = 0;
        bool isNegative = false;
        size_t startIndex = 0;
        
        // Check for sign
        if (number[0] == '+') {
            startIndex = 1;
        } else if (number[0] == '-') {
            isNegative = true;
            startIndex = 1;
        }
        
        // Process each character
        for (size_t i = startIndex; i < number.length(); i++) {
            char c = number[i];
            int digit = charToDigit(c);
            
            if (digit >= base) {
                throw std::invalid_argument("Digit '" + std::string(1, c) + 
                                          "' exceeds source base " + 
                                          std::to_string(base));
            }
            
            // Check for overflow
            if (result > (LLONG_MAX - digit) / base) {
                throw std::overflow_error("Number too large for conversion");
            }
            
            result = result * base + digit;
        }
        
        return isNegative ? -result : result;
    }
    
    // Convert from decimal to any base
    static std::string fromDecimal(long long number, int base) {
        if (number == 0) {
            return "0";
        }
        
        bool isNegative = number < 0;
        unsigned long long n = isNegative ? -static_cast<unsigned long long>(number) : number;
        std::string result;
        
        // Convert digits
        while (n > 0) {
            int digit = n % base;
            result += digitToChar(digit);
            n /= base;
        }
        
        // Reverse the string
        std::reverse(result.begin(), result.end());
        
        // Add sign if negative
        if (isNegative) {
            result = "-" + result;
        }
        
        return result;
    }
    
    // Convert fractional part between bases
    static std::string convertFractionalPart(const std::string& fractional, 
                                           int fromBase, 
                                           int toBase, 
                                           int precision) {
        double fractionalValue = 0.0;
        
        // Convert fractional part to decimal value
        for (size_t i = 0; i < fractional.length(); i++) {
            char c = fractional[i];
            int digit = charToDigit(c);
            if (digit >= fromBase) {
                throw std::invalid_argument("Digit '" + std::string(1, c) + 
                                          "' exceeds source base " + 
                                          std::to_string(fromBase));
            }
            fractionalValue += digit * std::pow(fromBase, -(static_cast<int>(i) + 1));
        }
        
        // Convert decimal fractional value to target base
        std::string result;
        double current = fractionalValue;
        
        for (int i = 0; i < precision && current > 0; i++) {
            current *= toBase;
            int digit = static_cast<int>(current);
            result += digitToChar(digit);
            current -= digit;
            
            // Break if we've reached zero (no more significant digits)
            if (std::abs(current) < 1e-10) {
                break;
            }
        }
        
        // If no fractional digits were generated, return "0"
        return result.empty() ? "0" : result;
    }
    
    // Convert character to digit value
    static int charToDigit(char c) {
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            return c - 'A' + 10;
        } else if (c >= 'a' && c <= 'z') {
            return c - 'a' + 10;
        } else {
            throw std::invalid_argument("Invalid character '" + 
                                      std::string(1, c) + "' in number");
        }
    }
    
    // Convert digit value to character
    static char digitToChar(int digit) {
        if (digit >= 0 && digit <= 9) {
            return '0' + digit;
        } else if (digit >= 10 && digit <= 35) {
            return 'A' + (digit - 10);
        } else {
            throw std::invalid_argument("Invalid digit value: " + 
                                      std::to_string(digit));
        }
    }
};

int main() {
    try {
        std::string number = "1111011";
        int fromBase = 2;  // decimal
        int toBase = 10;     // binary
        
        std::string result = BaseConverter::convertBase(number, fromBase, toBase);
        
        std::cout << number << " (base " << fromBase << ") = " 
                  << result << " (base " << toBase << ")" << std::endl;
                  
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}