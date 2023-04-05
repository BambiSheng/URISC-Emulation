#include <iostream>
#include <cstring>
#include <fstream>

#define NO_ERROR 0
#define SYNTAX_ERROR 1
#define UNDEFINED_TAG 2
#define FILE_READ_ERROR 3
#define END_COMMAND_LACK 4

using namespace std;

void perror(int error, int line)
{
  switch (error)
  {
  case NO_ERROR:
    break;
  case SYNTAX_ERROR:
    cout << "In line: " << line << "syntax error" << endl;
    exit(error);
    break;
  case UNDEFINED_TAG:
    cout << "In line: " << line << "Undefined tag" << endl;
    exit(error);
    break;
  case FILE_READ_ERROR:
    cout << "In line: " << line << "File read error" << endl;
    exit(error);
    break;
  case END_COMMAND_LACK:
    cout << "In line: " << line << "End command lack" << endl;
    exit(error);
    break;
  default:
    cout << "In line: " << line << "Unknown error" << endl;
    exit(error);
    break;
  }
}
void noteProcess(char *read)
{
  while (*read != '\0')
  {
    if (*read == ';')
      *read = '\0';
    read++;
  }
}
bool isBlank(char *read)
{
  char *temp = read;
  while (*temp != '\0')
  {
    if (*temp != ' ')
    {
      return false;
    }
    temp++;
  }
  return true;
}
bool isValidChar(char mychar)
{
  if (('A' <= mychar && mychar <= 'Z') || ('a' <= mychar && mychar <= 'z'))
    return true;
  else
    return false;
}

int isValidNum(char mynum)
{
  if ('0' <= mynum && mynum <= '9')
  {
    return mynum - '0';
  }
  else
    return -1;
}

class commandList;

class command
{
private:
  char *tag = NULL;
  char *aTag = NULL;
  char *bTag = NULL;
  char *cTag = NULL;
  command *a = NULL;
  command *b = NULL;
  command *c = NULL;
  command *next = NULL;
  int value = 0;
  int line = 0;
  bool type = 0;
  friend commandList;

public:
  command(char *read, int myLine);
  void run();
  int setValue(int newValue);
  void setType(bool newType);
  const int getValue();
  const int getLine();
  const char *getTag();
  const bool getType();
  ~command();
};

command::command(char *read, int myLine)
{
  char *temp = read;
  char *mark1 = read;
  char *mark2 = read;
  line = myLine;
  while (*temp == ' ')
  {
    temp++;
    if (*temp == '\0')
      perror(SYNTAX_ERROR, myLine);
  }
  mark1 = temp;
  while (*temp != ':')
  {
    temp++;
    if (*temp == '\0')
      perror(SYNTAX_ERROR, myLine);
  }
  mark2 = temp - 1;
  while (*mark2 == ' ')
  {
    mark2--;
    if (*mark2 == '\0')
      perror(SYNTAX_ERROR, myLine);
  }
  for (char *i = mark1; i <= mark2; i++)
  {
    if (!isValidChar(*i))
    {
      perror(SYNTAX_ERROR, myLine);
    }
  }
  *(mark2 + 1) = '\0';
  tag = new char[strlen(mark1) + 1];
  strcpy(tag, mark1);

  temp++;
  while (*temp == ' ')
  {
    temp++;
    if (*temp == '\0')
      perror(SYNTAX_ERROR, myLine);
  }
  mark1 = temp;
  while (isValidChar(*temp))
  {
    temp++;
  }

  if (*temp != ' ' && *temp != ',')
    perror(SYNTAX_ERROR, myLine);

  *temp = '\0';
  aTag = new char[strlen(mark1) + 1];
  strcpy(aTag, mark1);

  if (strcmp(aTag, "WORD") == 0)
  {
    temp++;
    while (*temp == ' ' || *temp == ',')
    {
      temp++;
      if (*temp == '\0')
        perror(SYNTAX_ERROR, myLine);
    }
    mark1 = temp;
    while (isValidNum(*temp) != -1)
    {
      temp++;
    }
    if (*temp != ' ' && *temp != ',' && *temp != '\0')
      perror(SYNTAX_ERROR, myLine);
    *temp = '\0';
    bTag = new char[strlen(mark1) + 1];
    strcpy(bTag, mark1);
    type = 1;
    value = stoi(bTag, 0, 10);
    if (!isBlank(temp))
      perror(SYNTAX_ERROR, myLine);

    //cout << "DEBUG LOG- -" << tag << ' ' << aTag << ' ' << bTag << ' ' << value << endl;
  }
  else
  {
    temp++;
    while (*temp == ' ' || *temp == ',')
    {
      temp++;
      if (*temp == '\0')
        perror(SYNTAX_ERROR, myLine);
    }
    mark1 = temp;
    while (isValidChar(*temp))
    {
      temp++;
    }

    if (*temp != ' ' && *temp != ',' && *temp != '\0')
      perror(SYNTAX_ERROR, myLine);
    bool jumpC = isBlank(temp);
    *temp = '\0';
    bTag = new char[strlen(mark1) + 1];
    strcpy(bTag, mark1);

    if (!jumpC)
    {
      temp++;
      while (*temp == ' ' || *temp == ',')
      {
        temp++;
        if (*temp == '\0')
          perror(SYNTAX_ERROR, myLine);
      }
      mark1 = temp;
      while (isValidChar(*temp))
      {
        temp++;
      }

      if (!isBlank(temp))
        perror(SYNTAX_ERROR, myLine);

      *temp = '\0';
      cTag = new char[strlen(mark1) + 1];
      strcpy(cTag, mark1);
      //cout << "DEBUG LOG- -" << tag << ' ' << aTag << ' ' << bTag << ' ' << cTag << ' ' << value << endl;
    }
    else
    {
      //cout << "DEBUG LOG- -" << tag << ' ' << aTag << ' ' << bTag << ' ' << value << endl;
    }
  }
}

void command::setType(bool newType)
{
  type = newType;
}
const bool command::getType()
{
  return type;
}
const int command::getValue()
{
  return value;
}
const int command::getLine()
{
  return line;
}
const char *command::getTag()
{
  char *cpTag = new char[strlen(tag) + 1];
  strcpy(cpTag, tag);
  return cpTag;
}

int command::setValue(int newValue)
{
  value = newValue;
  return value;
}

void command::run()
{

  if (strcmp(tag, "END") == 0)
    return;

  if (b->setValue(b->getValue() - a->getValue()) < 0)
  {
    if (c == NULL)
      next->run();
    else
      c->run();
  }
  else
  {
    next->run();
  }
}

command::~command()
{
}

class commandList
{
private:
  command *start = NULL;
  command *current = NULL;
  bool isEnd = false;

public:
  commandList(/* args */);
  ~commandList();
  void addCommand(command *newCommand);
  command *searchCommand(char *myCommandTag);
  void commandIni();
  void commandRun();
  void resPrint();
};
void commandList::addCommand(command *newCommand)
{

  if (start == NULL)
  {
    start = newCommand;
    current = start;
    start->next = NULL;
  }
  else
  {
    current->next = newCommand;
    current = newCommand;
    current->next = NULL;
  }
}
void commandList::resPrint()
{
  current = start;
  while (current != NULL)
  {
    if (current->getType() == true)
    {
      cout << current->getTag() << ' ' << current->getValue() << endl;
    }
    current = current->next;
  }
}

void commandList::commandRun()
{
  start->run();
}
void commandList::commandIni()
{
  current = start;
  while (current  != NULL)
  {
    if (!isEnd)
    {
      if (current->getType() == true)
        perror(SYNTAX_ERROR, current->getLine());
      if (((current->a) = searchCommand(current->aTag)) == NULL)
        perror(UNDEFINED_TAG, current->getLine());
      if (((current->b) = searchCommand(current->bTag)) == NULL)
        perror(UNDEFINED_TAG, current->getLine());
      if(current->cTag != NULL){
        if (((current->c) = searchCommand(current->cTag)) == NULL)
          perror(UNDEFINED_TAG, current->getLine());
      }
    }
    else
    {
      if (current->getType() == false)
        perror(SYNTAX_ERROR, current->getLine());
    }
    if(strcmp(current->getTag(), "END") == 0)
      isEnd = true;
    current = current->next;
  }

  if(!isEnd)
    perror(END_COMMAND_LACK, 0);
}

command *commandList::searchCommand(char *myCommandTag)
{
  command* currentMemory = current;
  command* temp = current;
  current = start;
  while (current != NULL)
  {
    if (strcmp(current->getTag(), myCommandTag) == 0)
    {
      temp = current;
      current = currentMemory;
      return temp;
    }
    current = current->next;
  }
  current = currentMemory;
  return NULL;
}

commandList::commandList(/* args */)
{
}

commandList::~commandList()
{
}

int main()
{
  commandList *myCommandList = new commandList();
  const char *address = "./code";
  ifstream fin;
  fin.open(address);
  if (!fin.is_open())
  {
    perror(FILE_READ_ERROR, 0);
  }
  char *read = new char[100];
  int line = 0;
  while (!fin.eof())
  {
    fin.getline(read, 100);
    line++;
    noteProcess(read);
    if (!isBlank(read))
    {
      command *temp = new command(read, line);
      myCommandList->addCommand(temp);
    }
    memset(read, 0, 100);
  }
  myCommandList->commandIni();
  cout<<"intput:"<<endl;
  myCommandList->resPrint();
  myCommandList->commandRun();
  cout<<"output:"<<endl;
  myCommandList->resPrint();
  return 0;
}