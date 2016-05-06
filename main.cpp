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

  Token() {
    mX = -1;
    mY = -1;
  } // Token()

  Token( string str ) {
    mToken = str;
    mX = -1;
    mY = -1;
  } // Token()

  Token( string str, int x, int y ) {
    mToken = str;
    mX = x;
    mY = y;
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
  vector<string> mTable3;
  // void      -> ( params )
  // if, while -> ( boolExp )
  // else, do  -> { stmt }

  Table() {
    mTable1 = GetTable1();
    mTable2 = GetTable2();
    mTable3 = GetTable3();
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
    string strArray[] = { "void", "if", "while", "else", "do" };
    vector<string> table3;
    for ( int i = 0 ; i < 5 ; i++ )
      table3.push_back( strArray[i] );
    return table3;
  } // GetTable3()
}; // class Table

// /////////////////////////////////////////////////////////////////////////////
//                                 Global                                     //
// /////////////////////////////////////////////////////////////////////////////

typedef vector<Token> OneLineToken;
vector<OneLineToken> gAllLineToken;
vector<OneLineToken> gAllFunctionToken;
Table gTable;
Index gIndex; // index of gAllLineToken

// /////////////////////////////////////////////////////////////////////////////
//                                 IsOO                                       //
// /////////////////////////////////////////////////////////////////////////////

bool IsTable1( string str ) {
  for ( int i = 0 ; i < gTable.mTable1.size() ; i++ )
    if ( str == gTable.mTable1[i] )
      return true;
  return false;
} // IsTable1()

bool IsTable2( string str ) {
  for ( int i = 0 ; i < gTable.mTable2.size() ; i++ )
    if ( str == gTable.mTable2[i] )
      return true;
  return false;
} // IsTable2()

bool IsTable3( string str ) {
  for ( int i = 0 ; i < gTable.mTable3.size() ; i++ )
    if ( str == gTable.mTable3[i] )
      return true;
  return false;
} // IsTable3()

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

Token PeekCurrentToken() {
  // PrintNowFunction( "PeekCurrentToken" );
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

  return PeekCurrentToken();
} // PeekCurrentToken()

Token GetCurrentToken() {
  // PrintNowFunction( "GetCurrentToken" );
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

  return GetCurrentToken();
} // GetCurrentToken()

Token PeekToken() {
  return PeekCurrentToken();
} // PeekToken()

Token GetToken() {
  return GetCurrentToken();
} // GetToken()

// /////////////////////////////////////////////////////////////////////////////
//                               sub function                                 //
// /////////////////////////////////////////////////////////////////////////////

bool VOID() {
  if ( PeekToken().mToken != "void" )
    return false;
  GetToken();
  return true;
} // VOID()

bool RETURN() {
  if ( PeekToken().mToken != "return" )
    return false;
  GetToken();
  return true;
} // RETURN()

bool IF() {
  if ( PeekToken().mToken != "if" )
    return false;
  GetToken();
  return true;
} // IF()

bool ELSE() {
  if ( PeekToken().mToken != "else" )
    return false;
  GetToken();
  return true;
} // ELSE()

bool WHILE() {
  if ( PeekToken().mToken != "while" )
    return false;
  GetToken();
  return true;
} // WHILE()

bool DO() {
  if ( PeekToken().mToken != "do" )
    return false;
  GetToken();
  return true;
} // DO()

bool PP() {
  if ( PeekToken().mToken != "++" )
    return false;
  GetToken();
  return true;
} // PP()

bool MM() {
  if ( PeekToken().mToken != "--" )
    return false;
  GetToken();
  return true;
} // MM()

bool TE() {
  if ( PeekToken().mToken != "*=" )
    return false;
  GetToken();
  return true;
} // TE()

bool DE() {
  if ( PeekToken().mToken != "/=" )
    return false;
  GetToken();
  return true;
} // DE()

bool RE() {
  if ( PeekToken().mToken != "%=" )
    return false;
  GetToken();
  return true;
} // RE()

bool PE() {
  if ( PeekToken().mToken != "+=" )
    return false;
  GetToken();
  return true;
} // PE()

bool ME() {
  if ( PeekToken().mToken != "-=" )
    return false;
  GetToken();
  return true;
} // ME()

// /////////////////////////////////////////////////////////////////////////////
//                              compound_statement                            //
// /////////////////////////////////////////////////////////////////////////////

bool Declaration() {
  if ( !Type_specifier() )
    return false;
  if ( !Identifier() )
    return false;
  if ( !Rest_of_declarators() )
    return false;

  return true;
} // Declaration()

// /////////////////////////////////////////////////////////////////////////////
//                      function_definition_or_declarators                    //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_declarators() {
  if ( PeekToken().mToken == "[" ) {
    GetToken();
    if ( !Constant() )
      return false;
    if ( PeekToken().mToken != "]" )
      return false;
    GetToken();
  } // if

  while ( PeekToken().mToken == "," ) {
    GetToken();
    if ( !Identifier() )
      return false;
    if ( PeekToken().mToken == "[" ) {
      GetToken();
      if ( !Constant() )
        return false;
      if ( PeekToken().mToken != "]" )
        return false;
      GetToken();
    } // if
  } // while

  if ( PeekToken().mToken != ";" )
    return false;

  return true;
} // Rest_of_declarators()

// /////////////////////////////////////////////////////////////////////////////
//                            formal_parameter_list                           //
// /////////////////////////////////////////////////////////////////////////////

bool Constant() {
  string mToken = PeekToken().mToken, aCharToString = "";
  aCharToString += mToken[0];
  if ( IsEnChar( aCharToString ) || IsTable1( mToken ) || IsTable2( mToken ) || IsTable3( mToken ) )
    return false;
  GetToken();
  return true;
} // Constant()

// /////////////////////////////////////////////////////////////////////////////
//                        function_definition_without_ID                      //
// /////////////////////////////////////////////////////////////////////////////

bool Formal_parameter_list() {
  if ( !Type_specifier )
    return false;
  if ( PeekToken().mToken == "&" )
    GetToken();
  if ( !Identifier() )
    return false;
  if ( PeekToken().mToken == "[" ) {
    GetToken();
    if ( !Constant() )
      return false;
    if ( PeekToken().mToken != "]" )
      return false;
    GetToken();
  } // if

  if ( PeekToken().mToken == "," ) {
    GetToken();
    return Formal_parameter_list();
  } // if

  return true;
} // Formal_parameter_list()

bool Compound_statement() {
  if ( PeekToken().mToken != "{" )
    return false;
  GetToken();
  if ( Declaration() || Statement() ) {
    // do nothing
  } // if

  if ( PeekToken().mToken != "}" )
    return false;

  return true;
} // Compound_statement()

// /////////////////////////////////////////////////////////////////////////////
//                                definition                                  //
// /////////////////////////////////////////////////////////////////////////////

bool Identifier() {
  string mToken = PeekToken().mToken, aCharToString = "";
  aCharToString += mToken[0];
  if ( !IsEnChar( aCharToString ) || IsTable1( mToken ) || IsTable2( mToken ) || IsTable3( mToken ) )
    return false;
  GetToken();
  return true;
} // Identifier()

bool Function_definition_without_ID() {
  if ( PeekToken().mToken != "(" )
    return false;
  GetToken();
  if ( VOID() || Formal_parameter_list() ) {
    // do nothing
  } // if
  if ( PeekToken().mToken != ")" )
    return false;
  GetToken();
  if ( !Compound_statement() )
    return false;

  return true;
} // Function_definition_without_ID()

bool Type_specifier() {
  if ( !IsTable1( PeekToken.mToken ) )
    return false;
  GetToken();

  return true;
} // Type_specifier()

bool Function_definition_or_declarators() {
  if ( !Function_definition_without_ID() && ! !Rest_of_declarators() )
    return false;

  return true;
} // Function_definition_or_declarators()


// /////////////////////////////////////////////////////////////////////////////
//                           non_comma_expression                             //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_non_comma_expression() {
  if ( PeekToken().mToken != "?" )
    return false;
  GetToken();
  if ( !Expression() )
    return false;
  if ( PeekToken().mToken != ":" )
    return false;
  GetToken();
  if ( !Basic_expression() )
    return false;
  if ( Rest_of_non_comma_expression() ) {
    // do nothing
  } // if

  return true;
} // Rest_of_non_comma_expression()

// /////////////////////////////////////////////////////////////////////////////
//                           actual_parameter_list                            //
// /////////////////////////////////////////////////////////////////////////////

bool Non_comma_expression() {
  if ( !Basic_expression() )
    return false;
  if ( Rest_of_non_comma_expression() ) {
    // do nothing
  } // if

  return true;
} // Non_comma_expression()

// /////////////////////////////////////////////////////////////////////////////
//                    rest_of_Identifier_started_basic_exp                    //
// /////////////////////////////////////////////////////////////////////////////

bool Actual_parameter_list() {
  if ( !Non_comma_expression() )
    return false;
  while ( PeekToken().mToken == "," ) {
    GetToken();
    if ( !Non_comma_expression() )
      return false;
  } // while

  return true;
} // Actual_parameter_list()

bool Assignment_operator() {
  if ( PeekToken().mToken != "=" && !TE() && !DE() && !RE() && !PE() && !ME() )
    return false
  return true;
} // Assignment_operator()

// /////////////////////////////////////////////////////////////////////////////
//                          signed_basic_expression                           //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_Identifier_started_signed_basic_exp() {
  if ( PeekToken().mToken == "[" ) {
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != "]" )
      return false;
    GetToken();
    if ( PP() || MM() ) {
      // do nothing
    } // if

    if ( !Rest_of_maybe_logical_OR_exp() )
      return false;
  } // if
  else if ( PP() || MM() ) {
    if ( !Rest_of_maybe_logical_OR_exp() )
      return false;
  } // else if
  else if ( Rest_of_maybe_logical_OR_exp() ) {
    // do nothing
  } // else if
  else if ( PeekToken().mToken == "(" ) {
    GetToken();
    if ( Actual_parameter_list() ) {
      // do nothing
    } // if

    if ( PeekToken().mToken != ")" )
      return false;
    GetToken();
    if ( !Rest_of_maybe_logical_OR_exp() )
      return false;
  } // else if
  else
    return false;

  return true;
} // Rest_of_Identifier_started_signed_basic_exp()


// /////////////////////////////////////////////////////////////////////////////
//                               signed_unary_exp                             //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_Identifier_started_unary_exp() {
  if ( PeekToken().mToken == "(" ) {
    GetToken();
    if ( Actual_parameter_list() ) {
      // do nothing
    } // if

    if ( PeekToken().mToken != ")" )
      return false;
    GetToken();
  } // if
  else if ( PeekToken().mToken == "[" ) {
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != "]" )
      return false;
    GetToken();
    if ( PP() || MM() ) {
      // do nothing()
    } // if
  } // else if
  else if ( PP() || MM() ) {
    // do nothing
  } // else if

  return true;
} // Rest_of_Identifier_started_unary_exp()

// /////////////////////////////////////////////////////////////////////////////
//                                  unary_exp                                 //
// /////////////////////////////////////////////////////////////////////////////

bool Signed_unary_exp() {
  if ( Identifier() ) {
    if ( Rest_of_Identifier_started_unary_exp() ) {
      // do nothing
    } // if
  } // if
  else if ( Constant() ) {
    // do nothing
  } // else if
  else if ( PeekToken().mToken == "(" ) {
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != ")" )
      return false;
    GetToken();
  } // else if
  else
    return false;
  return true;
} // Signed_unary_exp()

// /////////////////////////////////////////////////////////////////////////////
//                            rest_of_maybe_mult_exp                          //
// /////////////////////////////////////////////////////////////////////////////

bool Unary_exp() {
  if ( Sign() ) {
    while ( Sign() ) {
      // do nothing
    } // while

    if ( !Signed_unary_exp() )
      return false;
  } // if
  else if ( Signed_unary_exp() ) {
    // do nothing
  } // else if
  else if ( PP() || MM() ) {
    if ( !Identifier() )
      return false;
    if ( PeekToken().mToken == "[" ) {
      GetToken();
      if ( !Expression() )
        return false;
      if ( PeekToken().mToken != "]" )
        return false;
      GetToken();
    } // if
  } // else if
  else
    return false;
  return true;
} // Unary_exp()

// /////////////////////////////////////////////////////////////////////////////
//                          rest_of_maybe_additive_exp                        //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_maybe_mult_exp() {
  while ( PeekToken().mToken == "*" || PeekToken().mToken == "/" || PeekToken().mToken == "%" )
    if ( !Unary_exp() )
      return false;

  return true;
} // Rest_of_maybe_mult_exp()

bool Maybe_mult_exp() {
  if ( !Unary_exp() )
    return false;
  if ( !Rest_of_maybe_mult_exp() )
    return false;
  return true;
} // Maybe_mult_exp()

// /////////////////////////////////////////////////////////////////////////////
//                           rest_of_maybe_shift_exp                          //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_maybe_additive_exp() {
  if ( !Rest_of_maybe_mult_exp() )
    return false;
  while ( PeekToken().mToken == "+" || PeekToken().mToken == "-" ) {
    GetToken();
    if ( !Maybe_mult_exp() )
      return false;
  } // while

  return true;
} // Rest_of_maybe_additive_exp()

bool Maybe_additive_exp() {
  if ( !Maybe_mult_exp() )
    return false;
  while ( PeekToken().mToken == "+" || PeekToken().mToken == "-" ) {
    GetToken();
    if ( !Maybe_mult_exp() )
      return false;
  } // while

  return true;
} // Maybe_additive_exp()

// /////////////////////////////////////////////////////////////////////////////
//                         rest_of_maybe_relational_exp                       //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_maybe_shift_exp() {
  if ( !Rest_of_maybe_additive_exp() )
    return false;
  while ( LS() || RS() )
    if ( !Maybe_additive_exp() )
      return false;
  return true;
} // Rest_of_maybe_shift_exp()

bool Maybe_shift_exp() {
  if ( !Maybe_additive_exp() )
    return false;
  while ( LS() || RS() )
    if ( !Maybe_additive_exp() )
      return false;
  return true;
} // Maybe_shift_exp()

// /////////////////////////////////////////////////////////////////////////////
//                          rest_of_maybe_equality_exp                        //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_maybe_relational_exp() {
  if ( !Rest_of_maybe_shift_exp() )
    return false;
  while ( PeekToken().mToken == "<" || PeekToken().mToken == ">" || LE() || GE() ) {
    if ( PeekToken().mToken == "<" || PeekToken().mToken == ">" )
      GetToken();
    else if ( !Maybe_shift_exp() )
      return false;
  } // while

  return true;
} // Rest_of_maybe_relational_exp()

bool Maybe_relational_exp() {
  if ( Maybe_shift_exp() )
    return false;
  while ( PeekToken().mToken == "<" || PeekToken().mToken == ">" || LE() || GE() ) {
    if ( PeekToken().mToken == "<" || PeekToken().mToken == ">" )
      GetToken();
    else if ( !Maybe_shift_exp() )
      return false;
  } // while

  return true;
} // Maybe_relational_exp()

// /////////////////////////////////////////////////////////////////////////////
//                          rest_of_maybe_bit_AND_exp                         //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_maybe_equality_exp() {
  if ( !Rest_of_maybe_relational_exp() )
    return false;
  while ( EQ() || NEQ() )
    if ( !Maybe_relational_exp() )
      return false;
  return true;
} // Rest_of_maybe_equality_exp()

bool Maybe_equality_exp() {
  if ( !Maybe_relational_exp() )
    return false;
  while ( EQ() || NEQ() )
    if ( !Maybe_relational_exp() )
      return false;
  return true;
} // Maybe_equality_exp()

// /////////////////////////////////////////////////////////////////////////////
//                         rest_of_maybe_bit_ex_OR_exp                        //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_maybe_bit_AND_exp() {
  if ( !Rest_of_maybe_equality_exp() )
    return false;
  while ( PeekToken().mToken == "&" ) {
    GetToken();
    if ( !Maybe_equality_exp() )
      return false;
  } // while

  return true;
} // Rest_of_maybe_bit_AND_exp()

bool Maybe_bit_AND_exp() {
  if ( !Maybe_equality_exp() )
    return false;
  while ( PeekToken().mToken == "&" ) {
    GetToken();
    if ( !Maybe_equality_exp() )
      return false;
  } // while

  return true;
} // Maybe_bit_AND_exp()

// /////////////////////////////////////////////////////////////////////////////
//                          rest_of_maybe_bit_OR_exp                          //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_maybe_bit_ex_OR_exp() {
  if ( !Rest_of_maybe_bit_AND_exp() )
    return false;
  while ( PeekToken().mToken == "^" ) {
    GetToken();
    if ( !Maybe_bit_AND_exp() )
      return false;
  } // while

  return true;
} // Rest_of_maybe_bit_ex_OR_exp()

bool Maybe_bit_ex_OR_exp() {
  if ( !Maybe_bit_AND_exp() )
    return false;
  while ( PeekToken().mToken == "^" ) {
    GetToken();
    if ( !Maybe_bit_AND_exp() )
      return false;
  } // while

  return true;
} // Maybe_bit_ex_OR_exp()

// /////////////////////////////////////////////////////////////////////////////
//                       rest_of_maybe_logical_AND_exp                        //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_maybe_bit_OR_exp() {
  if ( !Rest_of_maybe_bit_ex_OR_exp() )
    return false;
  while ( PeekToken().mToken == "|" ) {
    GetToken();
    if ( !Maybe_bit_ex_OR_exp() )
      return false;
  } // while

  return true;
} // Rest_of_maybe_bit_OR_exp()

bool Maybe_bit_OR_exp() {
  if ( !Maybe_bit_ex_OR_exp() )
    return false;
  while ( PeekToken().mToken == "|" ) {
    GetToken();
    if ( !Maybe_bit_ex_OR_exp() )
      return false;
  } // while

  return true;
} // Maybe_bit_OR_exp()

// /////////////////////////////////////////////////////////////////////////////
//                        rest_of_maybe_logical_OR_exp                        //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_maybe_logical_AND_exp() {
  if ( !Rest_of_maybe_bit_OR_exp() )
    return false;
  while ( AND() )
    if ( !Maybe_bit_OR_exp() )
      return false;
  return true
} // Rest_of_maybe_logical_AND_exp()

bool Maybe_logical_AND_exp() {
  if ( !Maybe_bit_OR_exp() )
    return false;
  while ( AND() )
    if ( !Maybe_bit_OR_exp() )
      return false;
  return true;
} // Maybe_logical_AND_exp()

// /////////////////////////////////////////////////////////////////////////////
//                             basic_expression                               //
// /////////////////////////////////////////////////////////////////////////////

bool Rest_of_Identifier_started_basic_exp() {
  if ( PeekToken().mToken == "[" ) { // 1
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != "]" )
      return false;
    GetToken();
    if ( Assignment_operator() ) {
      if ( !Basic_expression() )
        return false;
    } // if
    else if ( PP() || MM() ) {
      if ( !Rest_of_maybe_logical_OR_exp() )
        return false;
    } // else if
    else if ( Rest_of_maybe_logical_OR_exp() ) {
      // do nothing
    } // else if
    else
      return false;
  } // if
  else if ( Assignment_operator() ) { // 2
    if ( !Basic_expression() )
      return false;
  } // else if
  else if ( PP() || MM() ) { // 3
    if ( !Rest_of_maybe_logical_OR_exp() )
      return false;
  } // else if
  else if ( Rest_of_maybe_logical_OR_exp() ) { // 4
    // do nothing
  } // else if
  else if ( PeekToken().mToken == "(" ) { // 5
    GetToken();
    if ( Actual_parameter_list() ) {
      // do nothing
    } // if

    if ( PeekToken().mToken != ")" )
      return false;
    GetToken();
    if ( !Rest_of_maybe_logical_OR_exp() )
      return false;
  } // else if
  else
    return false;

  return true;
} // Rest_of_Identifier_started_basic_exp()

bool Rest_of_PPMM_Identifier_started_basic_exp() {
  if ( PeekToken().mToken == "[" ) {
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != "]" )
      return false;
    GetToken();
  } // if

  if ( !Rest_of_maybe_logical_OR_exp() )
    return false;

  return true;
} // Rest_of_PPMM_Identifier_started_basic_exp()

bool Signed_basic_expression() {
  if ( Identifier() ) {
    if ( !Rest_of_Identifier_started_signed_basic_exp() )
      return false;
  } // if
  else if ( Constant() ) {
    if ( !Rest_of_maybe_logical_OR_exp() )
      return false;
  } // else if
  else if ( PeekToken.mToken() == "(" ) {
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken.mToken() != ")" )
      return false;
    GetToken();
    if ( !Rest_of_maybe_logical_OR_exp() )
      return false;
  } // else if
  else
    return false;

  return true;
} // Signed_basic_expression()

bool Sign() {
  if ( PeekToken().mToken != "+" && PeekToken().mToken != "-" && PeekToken().mToken != "!" )
    return false;
  return true;
} // Sign()

bool Rest_of_maybe_logical_OR_exp() {
  if ( !Rest_of_maybe_logical_AND_exp() )
    return false;
  while ( OR() ) {
    if ( !Maybe_logical_AND_exp() )
      return false;
  } // while

  return true;
} // Rest_of_maybe_logical_OR_exp()

// /////////////////////////////////////////////////////////////////////////////
//                                expression                                  //
// /////////////////////////////////////////////////////////////////////////////

bool Basic_expression() {
  if ( Identifier() ) {
    if ( !Rest_of_Identifier_started_basic_exp() )
      return false;
  } // if
  else if ( PP() || MM() ) {
    if ( !Identifier() )
      return false;
    if ( !Rest_of_PPMM_Identifier_started_basic_exp() )
      return false;
  } // else if
  else if ( Sign() ) {
    while ( Sign() ) {
      // do nothing
    } // while

    if ( !Signed_basic_expression() )
      return false;
  } // else if
  else if ( Constant() ) {
    if ( !Rest_of_maybe_logical_OR_exp() )
      return false;
  } // else if
  else if ( PeekToken().mToken == "(" ) {
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != ")" )
      return false;
    GetToken();
    if ( !Rest_of_maybe_logical_OR_exp() )
      return false;
  } // else if
  else
    return false;

  return true;
} // Basic_expression()

bool Rest_of_expression() {
  if ( PeekToken().mToken == "," ) {
    GetToken();
    if ( !Basic_expression() )
      return false;
    if ( Rest_of_expression() ) {
      // do nothing
    } // if
  } // if
  else if ( PeekToken().mToken == "?" ) {
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != ":" )
      return false;
    GetToken();
    if ( !Basic_expression() )
      return false;
    if ( Rest_of_expression() ) {
      // do nothing
    } // if
  } // else if
  else
    return false;

  return true;
} // Rest_of_expression()

// /////////////////////////////////////////////////////////////////////////////
//                                statement                                   //
// /////////////////////////////////////////////////////////////////////////////

bool Expression() {
  if ( !Basic_expression() )
    return false;
  if ( Rest_of_expression() ) {
    // do nothing
  } // if

  return true;
} // Expression()

// /////////////////////////////////////////////////////////////////////////////
//                                user_input                                  //
// /////////////////////////////////////////////////////////////////////////////

bool Definition() {
  if ( VOID() ) {
    if ( !Identifier() )
      return false;
    if ( !Function_definition_without_ID() )
      return false;
  } // if
  else if ( Type_specifier() ) {
    if ( !Identifier() )
      return false;
    if ( !Function_definition_or_declarators() )
      return false;
  } // else if
  else
    return false;

  return true;
} // Definition()

bool Statement() {
  if ( PeekToken().mToken == ";" ) {
    GetToken();
  } // if
  else if ( Expression() ) {
    if ( PeekToken.mToken != ";" )
      return false;
    GetToken();
  } // else if
  else if ( RETURN() ) {
    if ( Expression() ) // 0 or 1
      if ( PeekToken().mToken != ";" )
        return false;
    if ( PeekToken().mToken != ";" )
      return false;
    GetToken();
  } // else if
  else if ( Compound_statement() ) {
    // do nothing
  } // else if
  else if ( IF() ) {
    if ( PeekToken().mToken != "(" )
      return false;
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != ")" )
      return false;
    GetToken();
    if ( !Statement() )
      return false;
    if ( ELSE() ) // 0 or 1
      if ( !Statement() )
        return false;
  } // if
  else if ( WHILE() ) {
    if ( PeekToken().mToken != "(" )
      return false;
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != ")" )
      return false;
    GetToken();
    if ( !Statement() )
      return false;
  } // else if
  else if ( DO() ) {
    if ( !Statement() )
      return false;
    if ( !WHILE() )
      return false;
    if ( PeekToken().mToken != "(" )
      return false;
    GetToken();
    if ( !Expression() )
      return false;
    if ( PeekToken().mToken != ")" )
      return false;
    GetToken();
    if ( PeekToken().mToken != ";" )
      return false;
    GetToken();
  } // else if
  else
    return false;

  return true;
} // Statement()

bool User_input() {
  if ( !Definition() && !Statement() )
    return false;
  while ( Definition() || Statement() ) ;

  return true;
} // user_input()

// /////////////////////////////////////////////////////////////////////////////
//                                   start                                    //
// /////////////////////////////////////////////////////////////////////////////

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
