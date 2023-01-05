 #include <bits/stdc++.h>
 using namespace std;
 struct MyPair
 {
     string binary;
     char ch;
     string s_bin;
     int freq;
     MyPair()
     {
         this->freq = 0;
     }
 };
 struct MinHeap
 {
     MinHeap *left, *right;
     int freq;
     char ch;
     string binary;
     MinHeap() {}
     MinHeap(int freq, char ch, string bin)
     {
         this->freq = freq;
         this->ch = ch;
         this->binary = bin;
         this->left = this->right = nullptr;
     }
 };
 struct MinH
 {
     int size;
     MinHeap **obj;
     MinH() {}
     MinH(int size)
     {
         this->size = size;
         obj = new MinHeap *[size]();
     }
 };
 void store_words(vector<char> &characters)
 {
     char ch = 'a';
     while (ch <= 'z')
     {
         characters.push_back(ch);
         ch++;
     }
     ch = 'A';
     while (ch <= 'Z')
     {
         characters.push_back(ch);
         ch++;
     }
     characters.push_back('.');
 }
 void initialize_words(vector<char> characters, vector<MyPair> &v)
 {
     for (int i = 0; i < v.size(); i++)
     {
         int idx = rand() % characters.size();
         char ch = '$';
         while (true)
         {
             if (characters.at(idx) != '$')
             {
                 v[i].ch = characters[idx];
                 characters[idx] = '$';
                 break;
             }
             else
                 idx = rand() % characters.size();
         }
     }
 }
 bool check_not_present(vector<MyPair> &v, string str)
 {
     for (int i = 0; i < v.size(); i++)
     {
         if (v[i].binary.compare(str) == 0)
         {
             v[i].freq += 1;
             return false;
         }
     }
     return true;
 }
 template <typename T>
 void Swap(T &obj, T &obj1)
 {
     T temp;
     temp = obj;
     obj = obj1;
     obj1 = temp;
 }
 void MinHeapify(MinH *minH, int i)
 {
     int l = 2 * i + 1;
     int r = 2 * i + 2;

     int smallest = i;
     if (l < minH->size && minH->obj[l]->freq < minH->obj[i]->freq)
         smallest = l;
     if (r < minH->size && minH->obj[r]->freq < minH->obj[smallest]->freq)
         smallest = r;

     if (smallest != i)
     {
         Swap(minH->obj[i], minH->obj[smallest]);
         MinHeapify(minH, smallest);
     }
 }
 void convert(MinH *minH)
 {
     for (int i = (minH->size - 2) / 2; i >= 0; i--)
         MinHeapify(minH, i);
 }
 MinHeap *extractMin(struct MinH *minH)
 {
     MinHeap *temp = minH->obj[0];
     minH->obj[0] = minH->obj[minH->size - 1];
     Swap(minH->obj[0], minH->obj[minH->size - 1]);

     --(minH->size);
     MinHeapify(minH, 0);
     return temp;
 }
 void insert(MinH *minH, MinHeap *minheap)
 {
     ++(minH->size);
     int i = minH->size - 1;
     while (i && minheap->freq < minH->obj[(i - 1) / 2]->freq)
     {
         minH->obj[i] = minH->obj[(i - 1) / 2];
         i = (i - 1) / 2;
     }

     minH->obj[i] = minheap;
 }
 MinHeap *Make_Huff_tree(vector<MyPair> &v)
 {
     for (int i = 0; i < v.size(); i++)
     {
         for (int j = 0; j < v.size() - 1; j++)
         {
             if (v[j].freq < v[j + 1].freq)
                 Swap(v[j], v[j + 1]);
         }
     }
     MinH *minH = new MinH(v.size());
     for (int i = 0; i < v.size(); i++)
     {
         MinHeap *o = new MinHeap(v[i].freq, v[i].ch, v[i].binary);
         minH->obj[i] = o;
     }
     MinHeap *left, *right, *top;
     convert(minH);
     while (minH->size != 1)
     {
         left = extractMin(minH);
         right = extractMin(minH);
         top = new MinHeap(left->freq + right->freq, '$', "");
         top->left = left;
         top->right = right;
         insert(minH, top);
     }
     return extractMin(minH);
 }
 void File_Read(vector<MyPair> &V, string &str)
 {
     ifstream file;
     file.open("sample2.8b");
     if (!file)
         return;
     int count = 0;
     char ch = file.eof();
     getline(file, str, ch);
     file.close();
     string s;
     for (int i = 0; i < str.size(); i++)
     {
         s += str[i];
         if ((i + 1) % 8 == 0 && i != 0)
         {
             if (check_not_present(V, s))
             {
                 MyPair p;
                 p.binary = s;
                 p.freq += 1;
                 V.push_back(p);
                 count++;
             }
             s = "";
         }
     }
 }
 struct s
 {
     string binary;
     string S_bin;
     char ch;
 };
 void store_in_file(string str)
 {
     ofstream fout;
     fout.open("8b_again.8b", ios::app);
     fout << str;
 }
 void print_codes(MinHeap *root, vector<s> &v, string str)
 {
     if (!root)
         return;
     if (root->ch != '$')
     {
         struct s S;
         S.binary = root->binary;
         S.S_bin = str;
         S.ch = root->ch;
         v.push_back(S);
     }
     print_codes(root->left, v, str + '0');
     print_codes(root->right, v, str + '1');
 }
 char get_char(vector<MyPair> v, string s)
 {
     for (int i = 0; i < v.size(); i++)
     {
         if (s.compare(v[i].binary) == 0)
             return v[i].ch;
     }
     return '$';
 }
 void store_words_in_file(vector<struct MyPair> v, string str)
 {
     ofstream fout;
     fout.open("8b_to_chars.txt", ios::out);
     string s;
     for (int i = 0; i < str.size(); i++)
     {
         s += str[i];
         if ((i + 1) % 8 == 0 && i != 0 || i == str.size() - 1)
         {
             char ch = get_char(v, s);
             fout << ch;
             s = "";
         }
     }
     fout.close();
 }
 string get_bin(vector<struct s> v, string str)
 {
     for (int i = 0; i < v.size(); i++)
     {
         if (str.compare(v[i].binary) == 0)
             return v[i].S_bin;
     }
     return "";
 }
 void store_binary_in_file(vector<struct s> v, string str)
 {
     ofstream fout;
     fout.open("nbin.b", ios::out);
     string s;
     for (int i = 0; i < str.size(); i++)
     {
         s += str[i];
         if ((i + 1) % 8 == 0 && i != 0 || i == str.size() - 1)
         {
             string a = get_bin(v, s);
             fout << a;
             s = "";
         }
     }
     fout.close();
 }
 void print(MinHeap *root)
 {
     if (root == nullptr)
         return;
     cout << root->ch << ",";
     print(root->left);
     print(root->right);
 }
 void store(string s)
 {
     ofstream fout;
     fout.open("made_8b.8b", ios::out);
     fout << s;
 }
 string store_in_8b(MinHeap *root, string str, int &i)
 {
     string s = "";
     while (i <= str.size())
     {
         if (root->ch != '$')
         {
             s += root->binary;
             return s;
         }
         if (str[i] == '0')
         {
             if (root->left)
             {
                 i++;
                 root = root->left;
             }
             else
                 return s;
         }
         else if (str[i] == '1')
         {
             if (root->right)
             {
                 i++;
                 root = root->right;
             }
             else
                 return s;
         }
         else
             return s;
     }
     return s;
 }
 void get_8b_file(MinHeap *root)
 {
     ifstream fin;
     fin.open("nbin.b");
     string s;
     char ch = fin.eof();
     getline(fin, s, ch);
     int i = 0;
     string str = "";
     while (i < s.size())
         str += store_in_8b(root, s, i);
     store(str);
 }
 int main()
 {
     srand(0);
     vector<MyPair> v;
     vector<char> characters;
     store_words(characters);
     string file_chars;
     File_Read(v, file_chars);
     initialize_words(characters, v);
     MinHeap *minheap = Make_Huff_tree(v);
     vector<s> Binary_codes;
     print_codes(minheap, Binary_codes, "");
     store_words_in_file(v, file_chars);
     store_binary_in_file(Binary_codes, file_chars);
     get_8b_file(minheap);
     return 0;
 }
