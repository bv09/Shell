#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>
#include <unistd.h>
using namespace std;
#define CmdPt(name) void name (vector<string> &args);
const int Shell_Line_Len = 1024;
map <string, int> Cmd_map;
int ID = 0;
struct Process_Struct {
    // data
    int id;
    string name;
    int state;
    PROCESS_INFORMATION pi;
};
map<int, Process_Struct> Process_List;
// prototype Cmd
CmdPt(HelpCmd)
CmdPt(ExitCmd)
CmdPt(DateCmd)
CmdPt(TimeCmd)
CmdPt(DirCmd)
CmdPt(StartCmd)
CmdPt(StopCmd)
CmdPt(ResumeCmd)
CmdPt(KillCmd)
CmdPt(ListCmd)
CmdPt(ClearCmd)
// pointer chi đến các hàm trên
// note: không cần & trước function vì C++ tự decay tên hàm thành địa chỉ
void (*ptr[])(vector<string> &) = {
    HelpCmd,
    ExitCmd,
    DateCmd,
    TimeCmd,
    DirCmd,
    StartCmd,
    StopCmd,
    ResumeCmd,
    KillCmd,
    ListCmd,
    ClearCmd,
};
// Command List
const vector<string> Cmd = {
    "help",
    "exit",
    "date",
    "time",
    "dir",
    "start",
    "stop",
    "resume",
    "kill",
    "list",
    "clear"
};
const vector<string> Cmd_Instruction = {
    "Provide command information for TinyShell.",
    "Exit TinyShell.exe",
    "Show current date.",
    "Show current date and time.",
    "Display a list of files and subdirectories in a directory.",
    "Excute a process in a new window with background(default) or foreground.",
    "Stop a process by its ID (Know its ID by 'list' command).",
    "Resume a suspended process by its ID (Know its ID by 'list' command).",
    "Kill a process by its ID or all by '-1' (Know its ID by 'list' command).",
    "List all background processes.",
    "clear the TinyShell screen."
};
// init : insert Cmd to Cmd_map with Key = name and Value = idx of Cmd in ptr[] 
void init () {
    int idx = 0;
    for (const auto &v : Cmd) {
        Cmd_map.insert({v, idx});
        idx++;
    }
}
// Check valid number
bool Check_valid (string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return 0;
    }
    return 1;
}
// Get MainName Process
string Get_Name_Process (string Name) {
    string MainName = "";
    for (int i = Name.length() - 1; i >= 0; i--) {
        if (Name[i] == '\\') {
            reverse(MainName.begin(), MainName.end());
            return MainName;
        }
        MainName += Name[i];
    }
    reverse(MainName.begin(), MainName.end());
    return MainName;
}
// đọc input
string read_line() {
    string input;
    getline(cin, input);
    if (input.length() > Shell_Line_Len) {
        cout << "Please enter less than 1024 chars" << "\n";
        return "";
    }
    return input;
}
// lowercase input và tách input ra thành các tham số 
vector <string> split_line (string &arg) {
    for (int i = 0; i < arg.length(); i++) {
        arg[i] =  ('A' <= arg[i] && arg[i] <= 'Z') ? arg[i] + 32 : arg[i]; 
    }
    vector <string> args;
    stringstream ss(arg);
    string word;
    while (ss >> word) {
        args.push_back(word);
    }
    return args;
}
// thực thi chương trình bằng cách kiểm tra lệnh
// tồn tại hay không và thực hiện nó
void excute_line (vector<string> &args) {
    if (!Cmd_map.count(args[0])) {
        cout << "'" << args[0] << "'" << " is not recognized as a command. Use 'help' to get more information.\n";
        return;
    }
    auto it = Cmd_map.find(args[0]);
    int idx = it->second;
    (*ptr[idx])(args);
}
// danh sách các lệnh và hướng đẫn
void HelpCmd (vector<string> &args) {
    if (args.size() > 1) {
        cout << "No arguments for this command.\n";
        return;
    }
    cout << "__________________________________________________________________________________________" << "\n";
    cout << "__________________________________________________________________________________________" << "\n";
    for (int i = 0; i < Cmd.size(); i++) {
        cout << Cmd[i] << "\t\t" << Cmd_Instruction[i] << '\n';         
    }
}
void DateCmd (vector<string> &args) {
    vector<string> Months = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December" };
    vector<string> Wdays = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    time_t now = time(&now);
    tm *t = localtime(&now);
    cout << Wdays[t->tm_wday] <<", "<< Months[t->tm_mon] <<" "<< t->tm_mday << "," << 1900 + t->tm_year << "\n";
}
void TimeCmd (vector<string> &args) {
    time_t now = time(&now);
    tm *t = localtime(&now);
    string rear = (t->tm_hour >= 0 && t->tm_hour <= 11) ? " AM" : " PM";
    int hour = (t->tm_hour > 12) ? t->tm_hour - 12 : t->tm_hour;
    cout << hour << ":" << t->tm_min << ":" << t->tm_sec << rear << '\n';
}
void DirCmd (vector<string> &args) {
    WIN32_FIND_DATAA fd;
    string name = "";
    string name_extension;
    bool previous_alpha_check = 1;
    if (args.size() == 1 || args[1] == "*") name = "*";
    else {
        for (int i = 0; i < args[1].length(); i++) {
            if (args[1][i] == '\\') {
                previous_alpha_check = 0;
                continue;
            }
            if (args[1][i] != ':' && args[1][i] != '\\') {
                if (!previous_alpha_check) name += "\\";
                previous_alpha_check = 1;
            } else previous_alpha_check = 0;
            name += args[1][i];
        }
        name += "\\*";
    }
    if (args.size() <= 2) name_extension = ".*";
    else name_extension = args[2];
    name += name_extension;
    LPCSTR file = name.c_str();
    cout << file << "\n";
    HANDLE h = FindFirstFileA(file, &fd);
    if (h == INVALID_HANDLE_VALUE) {
        cout << "Cannot find the directory.\n";
        return; 
    }
    else {
        cout << left << setw(6) << "Mode" << right << setw(22) << "LastWriteTime" << right << setw(15) << "Length" << " " << "Name" << '\n';
        cout << left << setw(6) << "----" << right << setw(22) << "-------------" << right << setw(15) << "------" << " " << "----" << '\n';
        do{ 
            //file attribute
            //DARHS
            string mode = "------";
            int Attribute = fd.dwFileAttributes;
            if (Attribute & FILE_ATTRIBUTE_DIRECTORY) mode[0] = 'd';
            if (Attribute & FILE_ATTRIBUTE_ARCHIVE) mode[1] = 'a';
            if (Attribute & FILE_ATTRIBUTE_READONLY) mode[2] = 'r';
            if (Attribute & FILE_ATTRIBUTE_HIDDEN) mode[3] = 'h';
            if (Attribute & FILE_ATTRIBUTE_SYSTEM) mode[4] = 's';
            //lastwritetime
            FILETIME ft = fd.ftLastWriteTime;
            SYSTEMTIME st;
            FileTimeToSystemTime(&ft, &st);
            cout << right << setw(6) << mode;
            string check = (st.wMinute < 10) ? "0": ""; 
            string DATE_DAY = to_string(st.wDay) + "/" + to_string(st.wMonth) + "/" + to_string(st.wYear);
            string DATE_HOUR = to_string(st.wHour) + ":" + check + to_string(st.wMinute);
            cout << right << setw(15) << DATE_DAY;
            cout << right << setw(7) << DATE_HOUR;
            // length
            unsigned long long Size = (fd.nFileSizeHigh << 31) + fd.nFileSizeLow;
            cout << right << setw(15) << Size << " ";
            //Name
            cout << fd.cFileName << "\n";

        }
        while (FindNextFileA(h, &fd) != 0);
        CloseHandle(h);
        return;
    }
}
void ExitCmd (vector<string> &args) {
    for (auto &it : Process_List) {
        PROCESS_INFORMATION pi = it.second.pi;
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    Process_List.clear();
    exit(0);
}
void ClearCmd (vector<string> &args) {
    system("cls");
    return;
}
void StartCmd (vector<string> &args) {
    if (args.size() == 1) {
        cout << "This shell support .exe and .bat\n";
        return;
    }
    int Mode = 0;
    if (args.size() == 3) {
        if (args[2] == "foreground") Mode = 1;
        else if (args[2] != "background") Mode = -1;
    } 
    
    if (args[1].find(".") == -1) {
        args[1] += ".exe";
    } 
    int len = args[1].size();
    cout << args[1] << "\n";
    if (len >= 4 && args[1].substr(len - 4) == ".exe") {
        if (Mode == -1) {
            cout << "Third argument should be 'background' or 'foreground' or empty(background) \n";
            return;
        }
        PROCESS_INFORMATION pi;
        STARTUPINFOA si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        LPCSTR _ProcessName = args[1].c_str();
        bool Error_Check = CreateProcessA(_ProcessName, NULL, NULL, NULL, false,
            CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
        if (!Error_Check) {
            cout << "Cannot find the file specified\n";
            return;
        }
        Process_List.insert({++ID, Process_Struct{ID, Get_Name_Process(_ProcessName), 0, pi}});
    }
}
void StopCmd (vector<string> &args) {
    if (args.size() == 1) {
        cout << "Please provide process ID to stop\n";
        return;
    }
    if (!Check_valid(args[1])) {
        cout << "Process ID must be a number\n";
        return;
    }   
    int pid = stoi(args[1]);
    if (!Process_List.count(pid)) {
        cout << "No process with this ID, please use 'list' for information\n";
        return;
    }
    if (Process_List[pid].state == 1) {
        cout << "Process is already stopped\n";
        return;
    }
    if (Process_List[pid].state == 0) {
        PROCESS_INFORMATION pi = Process_List[pid].pi;
        SuspendThread(pi.hThread);
        Process_List[pid].state = 1;
    }
}
void ResumeCmd (vector<string> &args) {
    if (args.size() == 1) {
        cout << "Please provide process ID to resume\n";
        return;
    }
    if (!Check_valid(args[1])) {
        cout << "Process ID must be a number\n";
        return;
    }
    int pid = stoi(args[1]);
    if (!Process_List.count(pid)) {
        cout << "No process with this ID, please use 'list' for information\n";
        return;
    }
    if (Process_List[pid].state == 0) {
        cout << "Process is already running\n";
        return;
    }
    if (Process_List[pid].state == 1) {
        PROCESS_INFORMATION pi = Process_List[pid].pi;
        ResumeThread(pi.hThread);
        Process_List[pid].state = 0;
    }
}
void KillCmd (vector<string> &args) {
    if (args.size() == 1) {
        cout << "Please provide process ID or -1 to kill all processes\n";
        return;
    }
    if (args[1] == "-1") {
        for (auto &it : Process_List) {
            PROCESS_INFORMATION pi = it.second.pi;
            TerminateProcess(pi.hProcess, 0);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            ID--;
        }
        Process_List.clear();
        return;
    }
    if (!Check_valid(args[1])) {
        cout << "Process ID must be a number\n";
        return;
    }
    int pid = stoi(args[1]);
    if (!Process_List.count(pid)) {
        cout << "No process with this ID, please use 'list' for information\n";
        return;
    }
    PROCESS_INFORMATION pi = Process_List[pid].pi;
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    Process_List.erase(pid);
    ID--;
}
void ListCmd (vector<string> &args) {
    cout << ID << "\n";
    cout << left << setw(9) << "ID" << left << setw(10) << "PID" 
    << left << setw(9) << "STATE" << left << setw(9) << "NAME" << '\n'; 
    string PROCESS_STATE[2] = {"RUNNING", "STOPPED"};
    for (auto it = Process_List.begin(); it != Process_List.end(); ) {
        PROCESS_INFORMATION pi = it->second.pi;
        int id = it->first;
        string name = it->second.name;
        string STATE = PROCESS_STATE[it->second.state];
        DWORD Exit_Code;
        GetExitCodeProcess(pi.hProcess, &Exit_Code);
        if (Exit_Code != 259) {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            it = Process_List.erase(it);
            ID--;
        }
        else {
            cout << left << setw(9) << id << left << setw(10) << pi.dwProcessId 
            << left << setw(9) << STATE << left << setw(9) << name << '\n';  
            ++it;
        }
    }   
}

int main() {
    SetConsoleTitle("TinyShell");
    init();
    while (1) {
        string input;
        vector <string> args;
        cout << "Shell>";
        input = read_line();
        if (input == "") continue;
        args = split_line(input);
        excute_line(args);
    }
    
}