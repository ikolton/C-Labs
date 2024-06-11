import VectorModule;

int main() {
    emcpp::Vector<int, 5, emcpp::SafePolicy> intVec;
    emcpp::Vector<double, 4, emcpp::SafePolicy> doubleVec;
    emcpp::Vector<std::string, 3, emcpp::SafePolicy> stringVec;

    intVec.set(0, 1);
    doubleVec.set(0, 1.1);
    stringVec.set(0, "hello");

    std::cout << intVec << std::endl;
    std::cout << doubleVec << std::endl;
    std::cout << stringVec << std::endl;

    return 0;
}
