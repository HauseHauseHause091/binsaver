#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>
#include <cctype>

std::string fileToBinaryString(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return "";
    }

    std::string binaryOutput;
    char byte;

    while (file.get(byte)) {
        binaryOutput += std::bitset<8>(static_cast<unsigned char>(byte)).to_string();
    }

    return binaryOutput;
}

std::string binaryToPrintableText(const std::string& binaryInput) {
    std::string text;

    for (size_t i = 0; i + 8 <= binaryInput.length(); i += 8) {
        std::string byteStr = binaryInput.substr(i, 8);
        char character = static_cast<char>(std::bitset<8>(byteStr).to_ulong());

        if (std::isprint(static_cast<unsigned char>(character))) {
            text += character;
        } else {
            text += '.'; // Replace non-printables with .
        }
    }

    return text;
}

int main() {
    std::string filePath = "";  

    std::string binaryData = fileToBinaryString(filePath);
    std::cout << "Binary output (first 512 bits): " << binaryData.substr(0, 512) << "\n";

    std::string printable = binaryToPrintableText(binaryData);
    std::cout << "\nExtracted printable text (first 512 chars):\n" << printable.substr(0, 512) << "\n";

    return 0;
}
