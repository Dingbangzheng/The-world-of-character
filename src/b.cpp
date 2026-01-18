            if (ly == y) {
                get = std::string("curl -s -L -O " + server) + std::to_string(x) + std::string(".y.z/.") + std::to_string(y) + std::string(".z/last_version_z");
                std::system(get.c_str();
                if (std::filesystem::exists("./last_version_z")) {
                    std::ifstream file_last_version_z("./last_version_z");
                    std::string string_last_version_z;
                    std::getline(file_last_version_z , string_last_version_z);
                    file_last_version_z.close();
                    std::sscanf(string_last_version_z.c_str() , "%d" , &lz);
                    std::filesystem::remove("./last_version_z");
                } else {
                    std::ofstream logs("./logs",std::ios::app);
                    timestamp = std::time(nullptr);
                    logs << timestamp << "-ERROR[From=launcher,ID=1]:Can not find \"last_version_z\" or there is no \"curl\" command." << std::endl;
                    logs.close();
                    std::cout << "\033[31;40mERROR[From=launcher,ID=1]:Can not find \"last_version_z\" or there is no \"curl\" command.\033[0m" << std::endl;
                }
                if (lz > z) {
                    std::filesystem::remove("./updatedata");
                    std::cout << "\033[93;40mThe game is being updated. Please maintain an internet connection; otherwise, unexpected errors may occur.\033[0m" << std::endl;
                    std::cout << "Download updatedata..." << std::endl;
                    get = std::string("curl -s -L -O " + server) + std::to_string(x) + std::string(".y.z/.") + std::to_string(y) + std::string(".z/updatedata");
                    std::system(get.c_str());
                    if (std::filesystem::exists("./updatedata")) {
                        std::ifstream update("./updatedata");
                        std::string name;
                        while (std::getline(update , name)) {
                            if (!name.empty() && name.back() == '\r') {//去除Windows文件中的\r
                                name.pop_back();
                            }
                            //todo
                        }
                        update.close();
                    } else {
                        std::ofstream logs("./logs",std::ios::app);
                        timestamp = std::time(nullptr);
                        logs << timestamp << "-ERROR[From=launcher,ID=1]:Can not find \"updatedata\" or there is no \"curl\" command." << std::endl;
                        logs.close();
                        std::cout << "\033[31;40mERROR[From=launcher,ID=1]:Can not find \"updatedata\" or there is no \"curl\" command.\033[0m" << std::endl;
                    }
                    std::filesystem::remove("./updatedata");
                    z = lz;
                }
            } else if(ly > y) {
                //todo
            }
 
