#include "engine\core\ISerializable.h"
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>


namespace fs = std::filesystem;

// Klasa pomocnicza do zapisu / odczytu obiektow do /z pliko w binarnych
class BinarySerializer {
public:

    // Zapis obiektu do pliku binarnego
    static bool save(const ISerializable& obj, const std::string& path) {

        std::ofstream file(path, std::ios::binary);  // otwiercie pliku w trybie binarnym
        if (!file.is_open()) {
            std::cerr << "Nie udalo się otworzyc pliku do zapisu: " << path << "\n";
            return false;
        }


        obj.serialize(file);
        file.close();
        return true;
    }


    // Wczytanie obiektu z pliku binarnego

    static bool load(ISerializable& obj, const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Nie udalo się otworzyc pliku do odczytu: " << path << "\n";
            return false;
        }



        obj.deserialize(file);
        file.close();
        return true;
    }

    // Funkcja pomocnicza
    static std::vector<std::string> listFiles(const std::string& folder, const std::string& extension = ".bin") {
        std::vector<std::string> foundFiles;


        for (const auto& entry : fs::directory_iterator(folder)) {
            if (entry.path().extension() == extension) {
                foundFiles.push_back(entry.path().string());
            }
        }

        return foundFiles;
    }
};
