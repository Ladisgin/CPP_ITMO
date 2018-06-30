//
// Created by Vladislav Kalugin on 30/06/2018.
//

#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>


size_t count_test = 0;
size_t count_pass_test = 0;
std::string dir = "";

void generate_file(const std::string &generate_file_name);

bool is_equal(const std::string &generate_file_name);

void generate_big_file(const std::string &generate_file_name);

void generate_good_file(const std::string &generate_file_name);

void generate_empty_file(const std::string &generate_file_name);

void test(const std::string &generate_file_name);

int main(int argc, char *argv[]) {
    std::string generate_file_name = "testing_file.in";
    dir = argv[0];
    for (size_t i = 0; i < 5; i++) {
        generate_empty_file(generate_file_name);
        test(generate_file_name);
    }

    for (size_t i = 0; i < 75; i++) {
        generate_file(generate_file_name);
        test(generate_file_name);
    }

    generate_big_file(generate_file_name);
    test(generate_file_name);


    generate_good_file(generate_file_name);
    test(generate_file_name);


    if (count_test == count_pass_test) {
        std::cout << count_pass_test << " test completed :)";
    } else {
        std::cout << count_pass_test << " from " << count_test << "completed :(";
    }
    return 0;
}

void test(const std::string &generate_file_name) {
    if (is_equal(generate_file_name)) {
        std::cout << "test: " << count_test << " complete" << std::endl;
        count_pass_test++;
    } else {
        std::cout << "test: " << count_test << " error :(" << std::endl;
    }
    count_test++;
    std::cout << std::endl;
}

bool is_equal(const std::string &generate_file_name) {


    std::string encd;
    encd = dir.substr(0, dir.length() - 12) + "encode ";
    encd += generate_file_name;
    system(encd.c_str());

    std::string decd;
    decd = dir.substr(0, dir.length() - 12) + "decode ";
    decd += generate_file_name + ".huff";
    system(decd.c_str());

    std::ifstream original_file(generate_file_name, std::ios_base::in | std::ios_base::binary);
    std::ifstream decode_file(generate_file_name + ".decode",
                                   std::ios_base::in | std::ios_base::binary);

    std::vector<char> buffer(4000, 0);
    std::vector<char> buffer_2(4000, 0);
    bool flag = true;
    long gc, gc_2;
    while (!original_file.eof() && !decode_file.eof() && flag) {
        original_file.read(buffer.data(), buffer.size());
        decode_file.read(buffer_2.data(), buffer_2.size());
        gc = original_file.gcount();
        gc_2 = decode_file.gcount();
        if (gc != buffer.size()) {
            buffer.resize(gc);
        }
        if (gc_2 != buffer_2.size()) {
            buffer_2.resize(gc_2);
        }
        if (buffer != buffer_2) {
            flag = false;
        }
    }
    return flag;
}

void generate_file(const std::string &generate_file_name) {
    srand(time(0));
    std::ofstream fout(generate_file_name, std::ios_base::out | std::ios_base::binary);
    std::vector<char> buffer(rand() % 8000);
    for (size_t l = 0; l < (rand() % 8000); l++) {
        for (size_t j = 0; j < buffer.size(); j++) {
            buffer[j] = static_cast<char>((rand() % 256) - 128);
        }
        fout.write(buffer.data(), buffer.size());
    }
    fout.close();
}

void generate_empty_file(const std::string &generate_file_name) {
    std::ofstream fout(generate_file_name, std::ios_base::out | std::ios_base::binary);
    fout.close();
}

void generate_big_file(const std::string &generate_file_name) {
    srand(time(0));
    std::ofstream fout(generate_file_name, std::ios_base::out | std::ios_base::binary);
    std::vector<char> buffer(8000);
    for (size_t l = 0; l < 10000; l++) {
        for (size_t j = 0; j < buffer.size(); j++) {
            buffer[j] = static_cast<char>((rand() % 256) - 128);
        }
        fout.write(buffer.data(), buffer.size());
    }
    fout.close();
}

void generate_good_file(const std::string &generate_file_name) {
    srand(time(0));
    std::ofstream fout(generate_file_name, std::ios_base::out | std::ios_base::binary);
    std::vector<char> buffer(8000);
    for (size_t l = 0; l < 10000; l++) {
        for (size_t j = 0; j < buffer.size(); j++) {
            buffer[j] = 33;
        }
        fout.write(buffer.data(), buffer.size());
    }
    fout.close();
}