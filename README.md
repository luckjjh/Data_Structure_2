# Data_Structure_2
# 1. is_balance function
입력 받은 수식이 괄호치기가 잘 되어 있다면 true를 return 하고 잘 되어있지 않다면 false를 return 하도록 return type을 bool type으로 하고 parameter는 수식을 받아야 하므로 String type value를 const reference로 받았습니다.
 괄호치기를 확인하기 위해서는 stack을 사용해 왼쪽 괄호가 들어온 경우 stack에 push하고 오른쪽 괄호가 들어오면 stack에 있는 괄호를 pop해 주면서 수식의 입력이 종료되었을 때 stack이 비어 있다면 괄호치기가 잘 되어 있는 것이고 stack이 비어 있지 않거나, 중간에 stack underflow가 생기는 경우 괄호치기가 잘 안 돼 있는 것입니다.
 이번 program은 ‘(’, ‘)’ 말고도 ‘{’ ,’[’ ,‘]’ ,‘}’ 을 사용할 수 있음으로 괄호치기를 확인하기 위해 위와 같은 조건에 추가로 조건을 걸었습니다. 1) 먼저 왼쪽 괄호는 기존과 같이 모두 push 하지만 2) pop을 할 경우 stack의 top에 위치하는 괄호와 입력된 오른쪽 괄호가 같은 경우에만 pop을 해야 하는 조건을 추가로 지정했습니다. Is_balance function의 코드는 다음과 같습니다.
 먼저 while문을 활용해 입력 받은 String value인 input을 처음부터 끝까지 훑어보도록 반복조건을 걸었습니다. 그리고 괄호치기를 확인하기 위한 char type의 stack parent를 선언해 주었습니다. 
코드의 흐름을 설명하자면 먼저 int type value ‘I’를 while문 한 루프마다 증가시켜 string value인 input을 한 char단위씩 훑습니다. 이때 왼쪽 괄호인 [ { ( 가 입력된 경우 모두 parent stack에 push 하도록 하고 왼쪽 괄호가 아닌 경우 else문을 통해 일반 입력 문자나 연산자들은 무시하고 오른쪽 괄호를 확인 합니다. 이때 오른쪽 괄호가 입력되었는데 stack이 비어 있는 경우는 괄호치기가 제대로 되지 않은 수식이므로 바로 false를 return하게 하였고, 그 아래 코드는 각각의 괄호들이 stack의 짝이 맞는 경우만 pop을 하도록 while문을 구성했습니다. 그리고 마지막 if문의 조건 empty()를 통해 stack이 비어 있으면 괄호치기가 잘된 수식이므로 true를 return하고 stack에 data 남아있는 경우 false를 return하도록 is_balance function을 구성해 놓았습니다.

# 2. make_post_fix function
 Make_post_fix function의 parameter는 앞선 is_balance function과 같게 String type value를 const reference로 받았습니다. Return type은 초기에 char type의 array로 return을 받으려고 하다가 String의 길이가 정해져 있지 않음으로 길이를 늘리고 줄이는 데에 특별한 제약이 없는 STL의 vector를 char type으로 return하도록 설계하였습니다.
 Function의 내부는 앞선 is_balance function과 같이 입력 받는 string 전체를 훑어봐야 하므로 while문의 ‘i’를 한 loop마다 증가시켜 input의 문자열 전체를 훑어볼 수 있도록 반복문을 구성해 주었습니다.
그리고 return받은 postfix 연산식을 저장할 char type의 vector operations와 input을 저장하고 값을 operations 로 넘길지 말지를 판단할 char type의 stack operators를 선언해 주었습니다.
 Infix수식을 postfix로 바꾸기 위해서는 먼저 operand와 operator를 구분해야 합니다. Operand인 a, b, c가 입력으로 들어온 경우 바로 결과를 return할 vector인 operations에 push하고, 괄호들이나 연산자인 @, #, &가 입력으로 들어온 경우 stack에 저장해 놓았다가 조건과 순서에 맞춰서 vector에 push해주어야 합니다. 코드를 흐름대로 설명을 하면 먼저 앞선 is_balance function과 같이 string을 훑어보는 while문은 동일하고 조건문을 보겠습니다. 조건문은 총 4개의 조건으로 나눠 놓았는데 1)왼쪽 괄호, 2)operands, 3)operator, 4)오른쪽 괄호 순으로 조건을 나눠 놓았습니다.
 첫번째 조건인 입력이 왼쪽 괄호 3개중 하나일때는 왼쪽 괄호의 경우, 왼쪽 괄호는 infix 수식을 postfix 수식으로 변경할 때 stack에 넣어두고 다음 연산자나 오른쪽 괄호의 입력에 영향을 주는 문자이므로 모두 operators stack에 push하였습니다.
두번째 조건인 operands도 비슷한 느낌으로 postfix수식으로 변경될 때 operand들은 순서대로 출력에 입력이 되므로 바로 결과를 return할 vector인 operations에 push 하였습니다.
세번째 조건은 operator입니다. Operator는 stack에 들어있는 data의 조건에 따라 입력이 달라집니다. 먼저 operators stack이 비어 있지 않고, stack의 제일 위에 위치하는 data인 top()이 ( { [ 이 아니고, 연산자들은 우선 순위가 있습니다. 우선순위에 따라 &는 @ #보다 우선순위가 높음으로 먼저 계산되어야 하고 @와 #는 왼쪽에 있는 operator를 먼저 계산해야 합니다. 그래서 입력되는 연산자가 stack 제일 위에 있는 연산자보다 우선순위가 낮거나 같으면 앞서 명시한 3개의 조건 중 1개가 위반될 때까지 stack 제일 위의 operator를 vector에 push 하고 stack 제일 위에 data를 pop하는 것을 반복합니다. 그리고 조건을 만족하지 못한다면 입력 받은 operator를 stack에 push합니다.
마지막 조건은 입력이 오른쪽 괄호 3개 중 하나일 때입니다. 오른쪽 괄호는 먼저 기존 stack에 있던 top() operator를 vector에 push하고 stack의 top() data를 pop해줍니다. 그리고 오른쪽 괄호와 짝이 맞는 괄호가 나올 때까지 while문의 조건을 통해 stack제일 위에 있는 연산자를 vector에 push하고 pop하는 것을 반복한 뒤 짝이 맞는 괄호가 나온 경우 while문 반복을 멈추고 왼쪽 괄호를 pop해주면서 입력에 대한 infix 수식을 postfix로 변경하는 코드를 마칩니다. 그리고 stack에 남아있는 data를 while문을 활용해 stack에 data가 없을 때까지 operator인 경우 vector에 push해주고 pop하고 괄호인 경우 pop만 하면서 vector에 입력을 마치고 vector를 반환해주면서 make_post_fix function 실행을 마칩니다. 

# 3. is_prime function
Is_prime function은 make_post_fix function을 코딩하던 도중 operator들의 우선순위를 구분하는 function이 필요하다 생각해 작성한 function입니다. 앞선 make_post_fix function을 보시면 입력이 operator일 때 while문의 조건으로 들어가 있는 것을 확인할 수 있습니다. 
 두개의 operator가 우선순위에 맞는지 아닌지를 판단하기 위해 return type은 bool type으로 하였고 parameter는 stack과 char변수를 받아 비교하는 형식으로 function을 설계했습니다. Make_post_fix fuction에서는 operators stack과 입력되는 char인 input[i] 를 parameter로 받았습니다. Function은 먼저 입력 받은 stack의 제일 위에 있는 top()을 char type value인 topO에 저장해 놓은 뒤 과제에 지정해 놓은 연산자 우선 순위에 따라 입력되는 연산자가 @, #이고 stack에 제일 위에 있는 연산자가 &인 경우 연산자 우선순위에 따라 true를 return하고, 입력되는 연산자와 stack 제일 위에 있는 연산자가 같은 우선순위인 경우도 true를 return하도록 하였습니다. 
그리고 나머지 경우는 모두 연산자 우선순위에 적합하지 않음으로 false를 return하도록 하였습니다.

# 4. read_calculate function
 Read_calculate function은 앞서 코딩한 function들을 이용해 입력 받은 수식을 계산하는 function입니다. Function의 return type은 a, b, c중 하나로 출력되므로 char type으로 하였고 parameter는 수식을 입력 받아야 하므로 string type value인 input과 operations.txt를 참고해 수식을 계산해야 하므로 operations.txt의 연산자들 마다 입력에 따른 출력을 저장해 놓을 3x3 array 3개를 parameter로 받아 총 4개의 parameter를 받았습니다.  Read_calculate function에 입력으로 받을 string type의 input은 infix 수식이므로 postfix 수식으로 변경하고 저장해 주기위한 공간인 char type의 vector postFix를 선언해 주었습니다. 그리고 make_post_fix function을 활용해 input을 postfix 수식으로 변경한 뒤 vector에 저장하고 연산을 진행할 stack인 char type의 stack result와 postFix vector를 훑어볼 vector iterator it를 선언했습니다.
 For 반복문으로 it를 증가시키며 postfix 수식이 저장된 vector를 훑어보게 하였고, 먼저 수식의 제일 앞에 있는 operand를 result stack에 push한뒤 if문을 통해 result stack에 들어간 입력이 @ # &와 같은 operator인지 확인한 후 operator인 경우 switch case문을 활용해 각 연산자에 따라 입력 받은 두개의 operand를 확인하고 해당하는 연산자의 결과가 저장되어 있는 array에 접근해 특정 operator에 따른 두 operand의 결과 값을 stack에 push하는 것을 반복해 모든 postfix 수식을 훑게 되면 result stack의 top에 수식을 결과 값이 저장되게 하였고 result.top()을 return하며 수식 계산을 마치도록 하였습니다.

# 5. main function
Main 문은 먼저 operations.txt에서 operation에 대한 정보를 입력 받아야 하므로 STL에 있는 fstream이라는 library를 추가해 파일의 정보를 다뤘습니다. 그리고 operations.txt 파일에 있는 각 operator들의 연산 결과를 각각 따로 저장해야겠다 생각해 char type의 3x3 2차원 array를 3개 선언해 주었습니다. 각 operator에 따라 @는 atOper, #은 sharpOper, &는 andOper로 이름을 정했습니다.
 Ifstream type의 변수 inputOper로 현재 workspace에 있는 operations.txt파일에 접근하고 파일을 열어주었습니다. 그리고 STL String을 추가해 getline function을 활용했는데, getline function은 여러 줄로 구성된 String type의 data 한 줄마다 string type의 buffer에 저장할 수 있는 function입니다. 이런 function을 이용해 각 operator에 해당되는 결과값을 2차원 array에 저장하였습니다.  파일을 getline function을 통해 훑어 볼 때 반복은 while문을 사용하고 조건은 ! inputOper.eof(), (eof=End Of File) inputOper가 연 파일의 끝까지 line을 얻도록 하였습니다. Getline function을 이용해 operations.txt의 각 line을 array에 저장할 때 초기에 연산자 결과 사이의 공백은 생략되고 저장되는 줄 알았으나 시행착오를 격어 공백도 하나의 char로 인식해 저장된다는 것을 알게 되고 array에 data를 저장하는 2중 for문에 if 조건문을 추가해 문자가 ‘ ’이 아닌 경우만 array 입력이 되도록 하였습니다.
 각 연산자에 대한 결과 값들을 각각의 2차원 array에 저장을 마친 뒤 inputOper.close() 구문을 통해 사용을 마친 operations.txt 파일을 닫아주고 입력을 받을 string type value인 input과 결과를 출력할 char type value result를 선언해 주고 입력은 “EOI”가 들어올 때까지 계속 받아야 하므로 while문을 무한 반복문으로 만들어주고 입력이 EOI가 되면 if문을 통해 break하고 반복문을 탈출한 뒤 program을 마치도록 설정해 놓았습니다.
 수식이 입력된다면 if문의 조건인 is_balance function을 통해 input이 괄호치기가 잘 되어있는 경우에만 read_calculate function을 통해 계산을 하도록 하였고, 만약 괄호치기가 잘 안돼 있는 경우 is_balance function은 false를 반환해 else문에 있는 “Error!”를 출력하고 다음 수식을 계속 진행할 수 있도록 continue 구문을 사용하였습니다.


