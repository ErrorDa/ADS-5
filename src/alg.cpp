// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include <iostream>
#include "tstack.h"

int Prior(char pro) {
    switch (pro) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
      return 2;
    case '-':
      return 2;
    case '*':
      return 3;
    case '/':
      return 3;
    default:
        return -1;
    }
}

int Calc(char operat, int left, int right) {
    switch (operat) {
    case '+':
        return left + right;
        break;
    case '-':
        return left - right;
        break;
    case '*':
        return left * right;
        break;
    case '/':
        return left / right;
        break;
    default:
        return 0;
    }
}

std::string infx2pstfx(std::string inf) {
    char fr = 0;
    TStack <char, 500> st1;
    std::string str;
    for (int i = 0; i < inf.length(); i++) {
        int Pr = Prior(inf[i]);
        if (Pr > -1) {
            if ((Pr == 0 || Pr > Prior(fr) ||
                st1.Empty()) && inf[i] != ')') {
                if (st1.Empty())
                    fr = inf[i];
                st1.push(inf[i]);
            } else if (inf[i] == ')') {
                while (st1.get() != '(') {
                    str.push_back(st1.get());
                    str.push_back(' ');
                    st1.del();
                }
                st1.del();
                if (st1.Empty())
                    fr = 0;
            } else {
                while (!st1.Empty() && Prior(st1.get()) >= Pr) {
                    str.push_back(st1.get());
                    str.push_back(' ');
                    st1.del();
                }
                if (st1.Empty())
                    fr = inf[i];
                st1.push(inf[i]);
            }
        } else {
            str.push_back(inf[i]);
            str.push_back(' ');
        }
    }
    while (!(st1.Empty())) {
        str.push_back(st1.get());
        str.push_back(' ');
        st1.del();
    }
    str.erase(str.end() - 1, str.end());
    return str;
}

int eval(std::string post) {
    TStack <int, 500> st2;
    int res = 0, left = 0, right = 0;
    for (int i = 0; i < post.length(); i++) {
        if ((Prior(post[i]) == -1) && post[i] != ' ') {
            st2.push(post[i] - '0');
        } else if (Prior(post[i]) > 1) {
            right = st2.get();
            st2.del();
            left = st2.get();
            st2.del();
            st2.push(Calc(post[i], left, right));
        }
    }
    res = st2.get();
  return res;
}
