# include <stdlib.h>
# include <iostream>
# include <string>
# include <sstream>
# include <vector>
# include <iomanip>

using namespace std;

static int uTestNum = -1;

// /////////////////////////////////////////////////////////////////////////////
//                               class & struct                               //
// /////////////////////////////////////////////////////////////////////////////

class Token {
public:
  string mToken;
  int mX;
  int mY;
  bool mIsRecord;

  Token() {
    mX = -1;
    mY = -1;
    mIsRecord = false;
  } // Token()

  Token( string str ) {
    mToken = str;
    mX = -1;
    mY = -1;
    mIsRecord = false;
  } // Token()

  Token( string str, int x, int y ) {
    mToken = str;
    mX = x;
    mY = y;
    mIsRecord = false;
  } // Token()
}; // class Token

class Identifier {
public:
  string mToken;
  float mValue;

  Identifier() {
    mValue = 0;
  } // Identifier()

  Identifier( string token, float value ) {
    mToken = token;
    mValue = value;
  } // Identifier()
}; // class Identifier

class Table {
public:
  vector<string> mTable1; // instruction
  vector<string> mTable2; // operator

  Table() {
    mTable1 = GetTable1();
    mTable2 = GetTable2();
  } // Table()

private:
  vector<string> GetTable1() {
    string strArray[] = { "int", "char", "int" };
    vector<string> table1;
    for ( int i = 0 ; i < 3 ; i++ )
      table1.push_back( strArray[i] );
    return table1;
  } // GetTable1()

  vector<string> GetTable2() {
    string strArray[] = { "+", "-", "*", "/", ";", "(", ")", ":",
                          ":=", "=", "<>", ">", "<", ">=", "<=", "//" };
    vector<string> table2;
    for ( int i = 0 ; i < 16 ; i++ )
      table2.push_back( strArray[i] );
    return table2;
  } // GetTable2()
}; // class Table

// /////////////////////////////////////////////////////////////////////////////
//                                 Print                                      //
// /////////////////////////////////////////////////////////////////////////////

void PrintOneLineToken( vector<Token> oneLineToken ) {
  for ( int i = 0; i < oneLineToken.size() ; i++ )
    cout << oneLineToken[i].mToken << " ";
} // PrintOneLineToken()

void PrintNowFunction( string str ) {
  cout << "now in " << str << endl;
} // PrintNowFunction()

// /////////////////////////////////////////////////////////////////////////////
//                                GetToken                                    //
// /////////////////////////////////////////////////////////////////////////////

void GetOneLineString( string &oneLineString ) {
  // PrintNowFunction( "GetOneLineString" );
  char *str1 = new char[ 100 ];
  cout << "> ";
  cin.getline( str1, 100 );
  oneLineString = str1;
  oneLineString += "\n";
} // GetOneLineString()

bool GetNumToken( string oneLineString, OneLineToken &oneLineToken, int &index ) {
  // PrintNowFunction( "GetNumToken" );
  string aCharToString, aTokenString;
  int dotNum = 1;
  for ( ; index < oneLineString.size() ; index++ ) {
    aCharToString = string();
    aCharToString += oneLineString[index];
    if ( aCharToString == "." )
      dotNum--;
    if ( IsANumChar( aCharToString ) || ( aCharToString == "." && dotNum > -1 ) ) {
      aTokenString += aCharToString;
    } // if
    else {
      // 所有不是數字都回傳
      index--;
      Token token( aTokenString, gAllLineToken.size(), oneLineToken.size() );
      oneLineToken.push_back( token );
      return true;
    } // else
  } // for

  cout << "GetNumToken Error" << endl;
  return false;
} // GetNumToken()

bool GetIdenToken( string oneLineString, OneLineToken &oneLineToken, int &index ) {
  // PrintNowFunction( "GetIdenToken" );
  string aCharToString, aTokenString;
  for ( ; index < oneLineString.size() ; index++ ) {
    aCharToString = string();
    aCharToString += oneLineString[index];
    if ( IsANumChar( aCharToString ) || RecognizedIDTokenHead( aCharToString ) ) {
      aTokenString += aCharToString;
    } // if
    else {
      // 不是數字或英文貨底線
      index--;
      Token token( aTokenString, gAllLineToken.size(), oneLineToken.size() );
      oneLineToken.push_back( token );
      return true;
    } // else
  } // for

  cout << "GetIdenToken Error" << endl;
  return false;
} // GetIdenToken()

bool GetTokenString( string oneLineString, OneLineToken &oneLineToken, int &index ) {
  // PrintNowFunction( "GetTokenString" );
  string aCharToString, aTokenString;
  aCharToString = string();
  aCharToString += oneLineString[index];
  while ( index < oneLineString.size() && )

} // GetTokenString()

bool SymbolOrRecognizedToken( string oneLineString, OneLineToken &oneLineToken, int &index ) {
  // PrintNowFunction( "SymbolOrRecognizedToken" );
  string aCharToString, aTokenString;
  aCharToString = string();
  aCharToString += oneLineString[index];
  if ( IsTable2( aCharToString ) ) {
    aTokenString += aCharToString;
    index++;
    if ( index < oneLineString.size() ) {
      aCharToString += oneLineString[index];
      if ( IsTable2( aCharToString ) ) {
        aTokenString = aCharToString;
      } // if
      else
        index--;
    } // if

    if ( aTokenString == ":" ) {
      // 回報錯誤
      // PrintUnrecognizedToken( aTokenString );
      return false;
    } // if
    else if ( aTokenString == "//" ) {
      index = oneLineString.size();
      return true;
    } // else if

    Token token( aTokenString, gAllLineToken.size(), oneLineToken.size() );
    oneLineToken.push_back( token );
    return true;
  } // if

  // PrintUnrecognizedToken( aCharToString );
  cout << "SymbolOrRecognizedToken error"
  return false;
} // SymbolOrRecognizedToken()

bool GetOneLineToken() {
  // PrintNowFunction( "GetOneLineToken" );
  string oneLineString, aCharToString;
  OneLineToken oneLineToken;

  GetOneLineString( oneLineString );
  for ( int i = 0 ; i < oneLineString.size() ; i++ ) {
    aCharToString = string();
    aCharToString += oneLineString[i];
    if ( IsANumChar( aCharToString ) || aCharToString == "." ) {
      GetNumToken( oneLineString, oneLineToken, i );
    } // if
    else if ( RecognizedIDTokenHead( aCharToString ) ) {
      GetIdenToken( oneLineString, oneLineToken, i );
    } // else if
    else if ( aCharToString == "\"" ) {
      GetTokenString( oneLineString, oneLineToken, i );
    } // else if
    else if ( aCharToString != " " && aCharToString != "\n" && aCharToString != "\t" ) {
      if ( !SymbolOrRecognizedToken( oneLineString, oneLineToken, i ) )
        return false;
    } // else if

    if ( oneLineToken.size() > 0 &&
         ( oneLineToken.back().mToken == "quit" || oneLineToken.back().mToken == "QUIT" ) ) {
      gAllLineToken.push_back( oneLineToken );
      return true;
    } // if
  } // for

  // PrintOneLineToken( oneLineToken );
  gAllLineToken.push_back( oneLineToken );
  return true;
} // GetOneLineToken()

int main() {
  string e, testNum;
  cout << "Program starts..." << endl;
  char *str1 = new char[ 100 ];
  cin.getline( str1, 100 );
  testNum = str1;
  uTestNum  = atof( testNum.c_str() );

  return 0;
}
