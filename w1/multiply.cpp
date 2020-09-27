#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

// Implement a recursive multiplication two positive integers.

std::pair<std::string, std::string> split_at(std::string s, int n) {
    const auto mid = s.size() / 2;
    return {
        std::string(s.begin(), s.begin() + n),
        std::string(s.begin() + n, s.end())
    };
}

// Source: https://www.geeksforgeeks.org/sum-two-large-numbers/.
std::string add(std::string str1, std::string str2) {
    // Before proceeding further, make sure length 
    // of str2 is larger. 
    if (str1.length() > str2.length()) 
        swap(str1, str2); 
  
    // Take an empty string for storing result 
    std::string str = ""; 
  
    // Calculate length of both string 
    int n1 = str1.length(), n2 = str2.length(); 
  
    // Reverse both of strings 
    std::reverse(str1.begin(), str1.end()); 
    std::reverse(str2.begin(), str2.end()); 
  
    int carry = 0; 
    for (int i=0; i<n1; i++) 
    { 
        // Do school mathematics, compute sum of 
        // current digits and carry 
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry); 
        str.push_back(sum%10 + '0'); 
  
        // Calculate carry for next step 
        carry = sum/10; 
    } 
  
    // Add remaining digits of larger number 
    for (int i=n1; i<n2; i++) 
    { 
        int sum = ((str2[i]-'0')+carry); 
        str.push_back(sum%10 + '0'); 
        carry = sum/10; 
    } 
  
    // Add remaining carry 
    if (carry) 
        str.push_back(carry+'0'); 
  
    // reverse resultant string 
    std::reverse(str.begin(), str.end()); 
  
    return str; 
}

std::string multiply(std::string lhs, std::string rhs, int depth = 0) {
    // Assuming valid input.

    // Base case.
    if (lhs.size() == 1 || rhs.size() == 1) {
		    const auto lhsi = std::stoi(lhs);
            const auto rhsi = std::stoi(rhs);
            const auto r = lhsi * rhsi;
            const auto result = std::to_string(r);
        
            return result;
    }


    if (lhs.size() < rhs.size()) {
        const auto c = lhs;
        lhs = rhs;
        rhs = c;
    }

    auto add_lhs = std::string();
    if (lhs.size() % 2 != 0) {
        add_lhs = "0";
    }

    lhs += add_lhs;

    auto add_rhs = std::string();
    if (lhs.size() != rhs.size()) {
        add_rhs = std::string(lhs.size() - rhs.size(), '0');
    }

    rhs += add_rhs;

    const auto n = std::min(lhs.size(), rhs.size());
    
    const auto [a, b] = split_at(lhs, n / 2);
    const auto [c, d] = split_at(rhs, n / 2);
    
    const auto ac = multiply(a, c, depth + 2);
    const auto ad = multiply(a, d, depth + 2);
    const auto bc = multiply(b, c, depth + 2);
    const auto bd = multiply(b, d, depth + 2);

    auto result = add(
            add(
                ac + std::string(n, '0'),
                add(ad, bc) + std::string(n / 2, '0')
            ),
            bd
    );

    result = std::string(result.begin(), result.end() - add_lhs.size() - add_rhs.size());

    return result;
}
