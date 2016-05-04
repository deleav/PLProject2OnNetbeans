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

class Index {
public:
  int mX;
  int mY;

  Index() {
    mX = -1;
    mY = -1;
  } // Index()

  Index( int x, int y ) {
    mX = x;
    mY = y;
  } // Index
}; // class Index

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
  vector<string> mTable1; // declare
  vector<string> mTable2; // operator
  vector<string> mTable3; // void      -> ( params )
  vector<string> mTable4; // if, while -> ( boolExp )
  vector<string> mTable5; // else, do  -> { stmt }

  Table() {
    mTable1 = GetTable1();
    mTable2 = GetTable2();
    mTable3 = GetTable3();
    mTable4 = GetTable4();
    mTable5 = GetTable5();
  } // Table()

private:
  vector<string> GetTable1() {
    string strArray[] = { "int", "float", "char", "bool", "string" };
    vector<string> table1;
    for ( int i = 0 ; i < 5 ; i++ )
      table1.push_back( strArray[i] );
    return table1;
  } // GetTable1()

  vector<string> GetTable2() {
    string strArray[] = { ";", "(", ")", "{", "}", "+", "-", "*", "/", "%", "<", ">", ">=", "<=", "==",
                          "!=", "&", "^", "|", "=", "||", "&&", "+=", "-=", "*=", "/=", "%=", "++", "--",
                          "<<", ">>", ",", "?", ":" };
    vector<string> table2;
    for ( int i = 0 ; i < 34 ; i++ )
      table2.push_back( strArray[i] );
    return table2;
  } // GetTable2()

  vector<string> GetTable3() {
    vector<string> table3;
    table3.push_back( "void" );
    return table3;
  } // GetTable3()

  vector<string> GetTable4() {
    vector<string> table4;
    table4.push_back( "if" );
    table4.push_back( "while" );
    return table4;
  } // GetTable4()

  vector<string> GetTable5() {
    vector<string> table5;
    table5.push_back( "else" );
    table5.push_back( "do" );
    return table5;
  } // GetTable5()
}; // class Table

// /////////////////////////////////////////////////////////////////////////////
//                                 Global                                     //
// /////////////////////////////////////////////////////////////////////////////

typedef vector<Token> OneLineToken;
vector<OneLineToken> gAllLineToken;
Table gTable;
Index gIndex; // index of gAllLineToken

// /////////////////////////////////////////////////////////////////////////////
//                                 IsOO                                       //
// /////////////////////////////////////////////////////////////////////////////

bool IsTable2( string str ) {
  for ( int i = 0 ; i < gTable.mTable2.size() ; i++ )
    if ( str == gTable.mTable2[i] )
      return true;
  return false;
} // IsTable2()

bool IsANumChar( string charStr ) {
  if ( charStr.size() == 1 && charStr >= "0" && charStr <= "9" )
    return true;

  return false;
} // IsANumChar()

bool IsEnChar( string charStr ) {
  if ( charStr.size() == 1 &&
       ( ( charStr >= "a" && charStr <= "z" ) || ( charStr >= "A" && charStr <= "Z" ) ) )
    return true;
  return false;
} // IsEnChar()

bool RecognizedIDTokenHead( string charStr ) {
  if ( charStr == "_" || IsEnChar( charStr ) )
    return true;
  return false;
} // RecognizedIDTokenHead()

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

bool GetTokenString( string &oneLineString, OneLineToken &oneLineToken, int &index, string &aTokenString ) {
  // PrintNowFunction( "GetTokenString" );
  string aCharToString;
  while ( index < oneLineString.size() && aCharToString != "\"" ) {
    aCharToString = string();
    aCharToString += oneLineString[index];
    aTokenString += aCharToString;
    index++;
  } // while

  if ( index >= oneLineString.size() ) {
    GetOneLineString( oneLineString );
    index = 0;
    return GetTokenString( oneLineString, oneLineToken, index, aTokenString );
  } // if
  else if ( aCharToString == "\"" ) { // get string
    Token token( aTokenString, gAllLineToken.size(), oneLineToken.size() );
    oneLineToken.push_back( token );
    return true;
  } // else if

  return false;
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

    Token token( aTokenString, gAllLineToken.size(), oneLineToken.size() );
    oneLineToken.push_back( token );
    return true;
  } // if
  else if ( aCharToString == "!" ) {
    aTokenString += aCharToString;
    index++;
    if ( index < oneLineString.size() ) {
      aCharToString += oneLineString[index];
      if ( IsTable2( aCharToString ) ) {
        aTokenString = aCharToString;
        Token token( aTokenString, gAllLineToken.size(), oneLineToken.size() );
        oneLineToken.push_back( token );
        return true;
      } // if
    } // if
  } // else if

  // PrintUnrecognizedToken( aCharToString );
  cout << "SymbolOrRecognizedToken error";
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
      string aTokenString = aCharToString;
      i++;
      GetTokenString( oneLineString, oneLineToken, i, aTokenString );
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

Token PeekToken() {
  // PrintNowFunction( "PeekToken" );
  if ( gIndex.mX > -1 )
    if ( gIndex.mX < gAllLineToken.size() && gIndex.mY + 1 < gAllLineToken[gIndex.mX].size() ) {
      // peek next token
      return gAllLineToken[gIndex.mX][gIndex.mY+1];
    } // if

  // call GetOneLineToken()
  if ( GetOneLineToken() ) {
    gIndex.mX++;
    gIndex.mY = -1;
  } // if

  return PeekToken();
} // PeekToken()

Token GetToken() {
  // PrintNowFunction( "GetToken" );
  if ( gIndex.mX > -1 )
    if ( gIndex.mX < gAllLineToken.size() && gIndex.mY + 1 < gAllLineToken[gIndex.mX].size() ) {
      // peek next token
      gIndex.mY++;
      return gAllLineToken[gIndex.mX][gIndex.mY];
    } // if

  // call GetOneLineToken()
  if ( GetOneLineToken() ) {
    gIndex.mX++;
    gIndex.mY = -1;
  } // if

  return GetToken();
} // GetToken()

bool Done() {
  if ( PeekToken().mToken != "Done" )
    return false;
  GetToken();
  if ( PeekToken().mToken != "(" )
    return false;
  GetToken();
  if ( PeekToken().mToken != ")" )
    return false;
  GetToken();
  if ( PeekToken().mToken != ";" )
    return false;

  return true;
} // Done()

bool Run() {
  while ( !Done() ) {

  } // while

  return true;
} // Run()

int main() {
  string e, testNum;
  cout << "Program starts..." << endl;
  char *str1 = new char[ 100 ];
  cin.getline( str1, 100 );
  testNum = str1;
  uTestNum  = atof( testNum.c_str() );

  while ( PeekToken().mToken != "Done" ) {
    cout << GetToken().mToken << endl;
  } // while

  return 0;
} // main()
