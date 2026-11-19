//
// Created by sam on 10/25/26.
//

#ifndef C___MRM_HPP
#define C___MRM_HPP

#include  <iostream>
#include  <stdexcept>
#include <concepts>
#include <fstream>

namespace MrMCtr{
    template<typename  T>
    class MemoryController {
    protected:
        T* MrM;
        int Index_of_MrM;
        int limit_OfMrM;
        // temp MrM and its limit
        T* temp_MrM;
        int limit_OfTemp;
        int Index_of_Temp;
        // =====END OF TEMP====
        // FLAGS:
        bool* USED_INDEX;
        bool* USED_tINDEX;
    public:
        MemoryController(int limit) {
            if (limit < 2) {
                std::string converted = std::to_string(limit);
                throw std::invalid_argument("NULL_POINTER = "+converted+"\nYes this is considered Null pointer \nnegative,or smaller than [2] cant exists");
            }
            MrM = new T[limit];
            USED_INDEX = new bool[limit]{};
            Index_of_MrM = 0;
            limit_OfMrM = limit;

            // just a random ass untilizier
            temp_MrM = nullptr;
            USED_tINDEX = nullptr;
            limit_OfTemp = 0;
            Index_of_Temp = 0;
        }
        ~MemoryController() {
            delete [] MrM;
            delete [] USED_INDEX;
            delete [] temp_MrM;
        }
// save() function does not care about anything it just erases it 
// if it reaches limit of memory user has given then program will run inti OverFlow/OverFlowTemp this is because save() works for temp too
        void save(T data) {
            if (Index_of_MrM < limit_OfMrM) {
                MrM[Index_of_MrM] = data;
                USED_INDEX[Index_of_MrM] = true;
                Index_of_MrM++;
            } else if (temp_MrM != nullptr && Index_of_Temp < limit_OfTemp) {
                temp_MrM[Index_of_Temp] = data;
                USED_tINDEX[Index_of_Temp] = true;
                Index_of_Temp++;
            } else {
                throw std::runtime_error("OverFlow/OverFlowTemp\n cannot put a data anymore temp and main memory is dead reset atleast one of them to contuine using");
            }
        }
        void erase(int sp_Index , T Changing_or_Zero=T()) {
            if (sp_Index >= 0 && sp_Index < limit_OfMrM) {
                MrM[sp_Index] = Changing_or_Zero;
                USED_INDEX[sp_Index] = false;
            }
        }
// erase() and iSave() can save/delete data on memory spesificed index and iSave has OverWrite feature user can make it FALSE or TRUE as you can see on the code
        void iSave(int SP_Index , T What_To_Write , std::string OverWriteMode="FALSE") {
            if (OverWriteMode == "FALSE") {
                if (SP_Index >= 0 && SP_Index < limit_OfMrM && !hasData(SP_Index)) {
                    MrM[SP_Index] = What_To_Write;
                    USED_INDEX[SP_Index] = true;
                } else {
                    throw std::invalid_argument("Out of Bounderies\n trying to type data to a Memory of Index that doesnt exist and theresa data existing");
                }
            } else if (OverWriteMode == "TRUE") {
                if (SP_Index >= 0 && SP_Index < limit_OfMrM) {
                    MrM[SP_Index] = What_To_Write;
                    USED_INDEX[SP_Index] = true;
                } else {
                    throw std::invalid_argument("Out of Bounderies\n trying to type data to a Memory of Index that doesnt exist and theresa data existing");
                }
            }
        }
// dynBig is used to make memory bigger if constructor is smaller then 1 MB which is 1.000.000
        void dynBig(int nw_Limit) {
            if (MrM == nullptr || nw_Limit < limit_OfMrM || nw_Limit > 1000000 || USED_INDEX == nullptr) {
                throw std::invalid_argument("NoPointer:\nCant make a pointer bigger if it doesnt exist or nullptr from delete()\nthis error will show up \nif limit is smaller than old one and \nbigger than 1 MB");
            }
            if (nw_Limit > limit_OfMrM && nw_Limit < 1000000) {
                T* BiggerMrM = new T[nw_Limit];
                bool* temp_Indexer = new bool[nw_Limit]{};
                for (int i = 0; i < limit_OfMrM; i++) {
                    BiggerMrM[i] = MrM[i];
                    temp_Indexer[i] = USED_INDEX[i];
                }
                limit_OfMrM = nw_Limit;
                delete [] MrM;
                delete [] USED_INDEX;
                Index_of_MrM = 0;
                MrM = BiggerMrM;
                USED_INDEX = temp_Indexer;
            }
        }
// these 2 func are for to give protected veriable to .cpp that is using this .hpp
        T getDataOnIndex(int index) {
            if (index >= 0 && index < limit_OfMrM) {
                return MrM[index];
            } else {
                throw std::invalid_argument("NotExistingIndex\n this flag becomes acvtive \nif getDataOnInxdex the Index parametr is not or \nbigger then 0 and smaller then \nlimit of memory");
            }
        }
        int getLimitMrM(std::string MainRTemp="MAIN") {
            if (MainRTemp == "MAIN") {
                return limit_OfMrM;
            } else if (MainRTemp == "TEMP") {
                return limit_OfTemp;
            } else {
                throw std::invalid_argument("Well uhh dont you see that it only has 2 values MAIN and TEMP");
            }
        }
// it resets every data of MrM(its T() so that it can set what is 0 for string)
        void reset() {
            for (int i = 0; i < limit_OfMrM; i++) {
                MrM[i] = T();
                USED_INDEX[i] = false;
            }
            Index_of_MrM = 0;
        }
// deletin memory and setting it to nullptr so that dynbig or other some functions doesnt give any segment fault or even worse undefined behaviour
        void delMrM() {
            if (MrM == nullptr) {
                throw std::invalid_argument("NullPointer\n no memory to delete");
            }
            delete[] MrM;
            delete[] USED_INDEX;
            Index_of_MrM = 0;
            limit_OfMrM = 0;
            USED_INDEX = nullptr;
            MrM = nullptr;
        }
        void reActivate(int lmt) {
            if (MrM == nullptr) {
                MrM = new T[lmt];
                USED_INDEX = new bool[lmt]{};
                limit_OfMrM = lmt;
                Index_of_MrM = 0;
            } else if (lmt < 2 || lmt > 1000000) {
                throw std::invalid_argument("ByPassingMrMLimit\n you cant bypass it limit is only 1 MB which is 1,000,000 if we type it as a decimal");
            } else {
                throw std::invalid_argument("ExistingMemory\n cant create a second Memory on one pointer while it exists");
            }
        }
        bool hasData(int index) const {
            return index >= 0 && index < limit_OfMrM && USED_INDEX[index];
        }
        bool hasDataTemp(int index) const {
            return index >= 0 && index < limit_OfTemp && USED_tINDEX[index];
        }
        void copyPasTo(int start , int end) {
            if (start >= 0 && end < limit_OfMrM && start < end && hasData(start)) {
                MrM[end] = MrM[start];
                USED_INDEX[end] = true;
            } else {
                throw std::logic_error("NoDataAvaibleToCopyPaste\n cant copy from start index to end IF\n 1) both of indexes has negative or end is bigger then limit\n2) if start has no data to hasData() gives false to start then this will show up\n3) if end is == start then you will see this error");
            }
        }
        void fillIndex(T What_TOWR , int start , int end) {
            if (start < 0 || end >= limit_OfMrM || start > end) {
                throw std::invalid_argument("NullIndexFiller\n cant fill rooms if start is smaller then end\n and bigger then end\nor end is bigger then limit of MrM");
            }
            for (int i = start; i <= end; i++) {
                MrM[i] = What_TOWR;
                USED_INDEX[i] = true;
            }
        }
        void countFullIndex(int start , int end) {
            if (!hasData(start) || !hasData(end) || end >= limit_OfMrM) {
                throw std::invalid_argument("NoAvaibleStartEnd\n cant count if start or end if they dont have data");
            }
            for (int i = start; i <= end; i++) {
                std::cout << i << " <-- Index||TrueOrFalse --> " << hasData(i) << std::endl;
            }
        }
        void compact() {
            T* compactMrM = new T[limit_OfMrM];
            bool* compacted = new bool[limit_OfMrM];
            int write = 0;
            for (int i = 0; i < limit_OfMrM; i++) {
                if (hasData(i)) {
                    compactMrM[write] = MrM[i];
                    compacted[write] = true;
                    write++;
                }
            }
            delete[] MrM;
            delete[] USED_INDEX;
            MrM = compactMrM;
            USED_INDEX = compacted;
            Index_of_MrM = 0;
        }

        void openTemp(int lmt) {
            if (lmt < 2 || lmt > 5000000) {
                throw std::invalid_argument("NullMrM\n you cant have a memory smaller then 0 or equal or bigger then 5 MB(Main MrM can go up to 1MB with dynBig but temp can go up to 5MB");
            }
            temp_MrM = new T[lmt];
            USED_tINDEX = new bool[lmt];
            Index_of_Temp = 0;
            limit_OfTemp = lmt;
        }

        void resetTemp() {
            for (int i = 0; i < limit_OfTemp; i++) {
                temp_MrM[i] = T();
            }
            if (temp_MrM == nullptr) {
                throw std::runtime_error("Cannot reset Temp theres no temp existing currently please make sure temp memory is active to use this control");
            }
        }

        void delTemp() {
            for (int i = 0; i < limit_OfTemp; i++) {
                temp_MrM[i] = T();
            }
            delete [] temp_MrM;
            delete [] USED_tINDEX;
            Index_of_Temp = 0;
            limit_OfTemp = 0;
            USED_tINDEX = nullptr;
            temp_MrM = nullptr;
        }

        // this codes thats under of this line are for debugging or just to make your life easier

        void setUSED(int index , bool to_what) {
            USED_INDEX[index] = to_what;
        }

        void setIndex(int IndexNumber , std::string setIndexMode="MAIN") {
            if (setIndexMode == "MAIN") {

            }
        }

        void dataOfEHIDX(std::string condional="NO" , std::string tempOrNot="NOT") {
            if (condional == "NO") {
                if (tempOrNot == "NOT") {
                    for (int i = 0; i < limit_OfMrM; i++) {
                        std::cout << i << " " << MrM[i] << std::endl;
                    }
                } else if (tempOrNot == "YES") {
                    for (int i = 0; i < limit_OfTemp; i++) {
                        std::cout << i << " " << temp_MrM[i] << std::endl;
                    }
                }
            }  else if (condional == "YES") {
                if (tempOrNot == "NOT") {
                    for (int i = 0; i < limit_OfMrM; i++) {
                        if (hasData(i)) {
                            std::cout << MrM[i] << std::endl;
                        }
                    }
                } else if (tempOrNot == "YES") {
                    for (int i = 0; i < limit_OfTemp; i++) {
                        if (hasDataTemp(i)) {
                            std::cout << i << " " << temp_MrM[i] << std::endl;
                        }
                    }
                }
            }
            if (MrM == nullptr ) {
                throw std::runtime_error("NoExistinMrMtoOutput\n this accours if memory is a null ptr usually this will show up \nIF main MrM is deleted and is nullptr\nmake sure that MrM is active while using this");
            }
        }
    };
//  DiskController is useless yet anyone can edit this i dont care about this
    class DiskController {
    protected:
        std::string path_Name;
    public:
        DiskController(std::string path_Name , std::string TypeOfWriting="W") {
            this->path_Name = path_Name;
            if (TypeOfWriting == "W") {
                std::fstream file(path_Name , std::ios::out | std::ios::in);
            }
        }
    };
}

#endif //C___MRM_HPP
