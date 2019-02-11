# 2018 KAKAO CODE FESTIVAL Preliminary source
My source code for 2018 KAKAO Code festival.

개인적으로 풀어본 2018 KAKAO 코드 페스티벌 예선 소스코드입니다.

많은 분들이 참고하셨으면 좋겠고 혹시 문의 사항이나, 제가 틀린 곳이 있다면 Issues나 이메일 주시면 바로 답장 드리겠습니다.

---

* 예선 공식 풀이 : http://tech.kakao.com/2018/08/09/code-festival-2018-round-1/

* 예선 BOJ 링크 : https://www.acmicpc.net/category/detail/1897

* 참고 링크
    * 예선 풀이 : [박트리님 블로그](https://baactree.tistory.com/49), [hongjun7님 블로그](https://hongjun7.tistory.com/169)
    * Union-Find: Disjoint Set : [yswon님 블로그](https://bowbowbow.tistory.com/26), [신기한 아이님 블로그](https://makefortune2.tistory.com/39)
    * Fenwick Tree : [Backjoon Online Judge](https://www.acmicpc.net/blog/view/21)
    * Parallel Binary Search : [자손9319님 블로그](https://jason9319.tistory.com/284)
    * Convex Hull Trick : [codedoc님 블로그](https://codedoc.tistory.com/11), [weeklyps님 블로그](https://www.weeklyps.com/entry/%EC%BB%A8%EB%B2%A1%EC%8A%A4-%ED%97%90-%ED%8A%B8%EB%A6%AD-Convex-Hull-Trick)
---
1. [**상금 헌터**](https://www.acmicpc.net/problem/15953) (성공)
    * 단순히 등수를 구해주고 상금을 출력해주면 됩니다.
    
2. [**인형들**](https://www.acmicpc.net/problem/15954) (성공)
    * 표준 편차를 구하는 문제입니다.
    * 표준 편차를 구할 때 [((a1 - m)^2 + ... + (an - m) ^2) / n] 도 가능하지만 [((a1^2 + ... + an^2) / n)  - m^2)]로 풀 수도 있습니다.
    * 합과 제곱합을 구할 때 이전에 사용한 값에서 가장 앞의 값을 빼고 가장 뒤에 값만 더하는 식으로 속도를 줄였습니다. O(n^2)
        * K가 3이고 이전 합이 m = n1 + n2 + n3 라면, 이후 합은 m = m - n1 + n4 가 됩니다. (m = n2 + n3 + n4)
    * 변수 오버플로우에 신경써야 합니다.
    
3. [**숏코딩**](https://www.acmicpc.net/problem/15956) (성공)
    * 정수, 영문자로 이뤄진 변수와 ==, !=, && 로 이루어진 식을 동치인 최소한의 식으로 줄이는 문제입니다.
    * 언제나 옳다면 "true"를 반환하는게 아니라 "1==1"과 같은 논리식을 반환해야합니다.
    * 코드 순서
        1. string이 입력으로 들어오면 이를 formula라는 구조체로 파싱.
        2. 식에서 논리식이 하나일 경우에 대해 처리.
        3. 1의 formula 구조체를 이용해 == 인 경우 동치로 하나로 묶어줌 (같은 키를 할당).
        4. != 인 경우 서로 다른 집합으로 할당, 만약 논리식 양쪽의 두 키가 동치라면 "1==0"을 출력 (다른 키를 할당)
        5. 3의 동치인 집합에서 서로 다른 정수가 있는지 확인해서 있다면 "1==0"을 출력.
        6. map 자료형을 가지고 3, 4에서 작업한 집합 마다 가장 길이가 짧은 변수 혹은 정수 순으로 정렬.
        7. == 인 경우 해당 키가 속한 집합에서 가장 길이가 짧은 변수나 정수를 할당함.
        8. != 인 경우 만약 논리식 좌우변이 같은 키를 가지면 "1==0"을 출력, 좌우변이 둘 다 정수라면 생략함,\
        set 변수로 현재 추가하려는 키 조합이 있는지 확인한 후 없으면 추가함.
        9. 7, 8의 조합을 가지고 string 출력을 만들어 출력함.

4. [**부스터**](https://www.acmicpc.net/problem/15955) (성공)
    * 처음에는 DFS나 BFS로 다 따라가야하나 생각했으나, 공부를 해본 결과 Union-find(Disjoint) 자료구조를 사용하면 되는 문제입니다.
    * 가까운 체크포인트쌍 (i, i + 1) 순으로 거리에 따라 정렬을 하고 해당 거리가 현재 쿼리의 HP 이하인 경우 Disjoint셋을 이용해서 체크포인트의 쌍끼리 합쳐주는걸 반복하고, 쿼리의 Start, End 체크포인트가 같은 집합에 있다고 하면 "YES"를 출력하면 됩니다.
        1. 먼저 입력으로 들어온 체크 포인트들을 X순, Y순에 따라 각각 따로 정렬해줍니다.
        2. 그 후 쿼리로 들어온 입력을 체력 X순으로 정렬해줍니다.
        3. 그리고 Priority queue에 X순, Y순으로 정렬된 체크포인트들을 자신과 바로 이웃한 (i, i + 1)인 체크포인트와의 거리에 따라 오름차순 정렬합니다.
        4. 현재 쿼리의 체력 제한 이하인 체크포인트 쌍들을 3의 Queue에서 빼냅니다.
        5. 해당 체크포인트들을 Disjoint셋을 이용하여 묶어 줍니다.
        6. Disjoint셋의 Find연산을 이용하여 쿼리에서 찾고자하는 시작점과 끝점이 같은 집합에 속해있다면 "YES" 아니라면 "NO"를 저장해둡니다.
        7. 원래 처음 쿼리의 순서대로 아웃풋을 냅니다.
            * 처음에 아웃풋을 낼 때 cout << "YES" << endl; 으로 했더니 시간초과가 났습니다. 이를 cout << "YES\n"; 으로 수정하니 시간안에 출력이됐습니다
            * **C++ 출력인 cout은 C의 printf 보다 속도가 느리니 속도가 중요할 때는 printf를 쓰는게 좋습니다.**

5. [**음악 추천**](https://www.acmicpc.net/problem/15957) (성공)
    * 처음에는 트리를 만들어서 각 노드에 자식들의 가수 정보와 해당 가수당 노드의 갯수를 저장해 놓으면 바로 점수 계산이 가능하다 생각하고 트리를 만들었습니다. 해당 방법이 속도면에서 괜찮긴 했지만 메모리를 너무 많이 잡아먹어 메모리 초과가 났습니다.
    * 그 후에는 트리의 DFS 순서대로 배열을 만들고, 해당 배열 범위에 값을 더해주는 방법을 Fenwick Tree를 이용해 구현하였습니다.
    * Fenwick Tree를 이용해 구현해도 가수가 10^9명까지 가능하여 너무 많아 각각에 대해 점수를 계산하기에는 시간이 너무 많이 걸렸습니다. 해당 문제는 인터넷을 참고하여 Parallel Binary Search (병렬 이진 검색)을 통하여 해결하였습니다.
    * 요약하자면 Fenwick Tree를 통해 점수를 구하다가 Parallel Binary Search로 점수가 넘는 구간을 탐색하였습니다.
    * Fenswick Tree의 경우 배열이 있을 때 배열 어떤 인덱스와 그 앞의 합과 Tree의 업데이트를 O(logN)시간 안에 계산할 수 있는 방법입니다. 저는 [**BOJ에서**](https://www.acmicpc.net/blog/view/21) 참고하였습니다.

6. [**프로도의 100일 준비**](https://www.acmicpc.net/problem/15958) (실패 - 시간초과)
    * 인풋이 히스토그램 모양이므로 데이터상 어떤 x에 대해서 [x의 좌측의 최대 사각형 + x의 우측의 최대 사각형]을 구하면 풀 수 있습니다.
    * 어떤 x에서 좌나 우로 훑으면서 높이 y와 가장 좌측 혹은 우측 x좌표를 list로 저장하고, 이후 x + 1에서 탐색할 경우 이전 list에서 필요 없는 요소들을 없애주고 이전 list의 가장 높은 y 보다 큰 경우만 새로 추가해줍니다.
    * 그 후 처음에는 Brute force하게 현재 좌측, 우측 list에 있는 모든 요소들에 대해서 각가의 Max 값을 구한 후 둘 을 더해 Max를 찾았으나 17%에서 시간 초과가 났습니다.
    * 공부를 하다보니 [**Convex Hull Trick**](https://codedoc.tistory.com/11)을 사용하여 직선들의 최대값을 O(logN) 시간 안에 찾는 방법이 있어서 적용해봤습니다. 하지만 오히려 처음보다 속도가 더 줄었습니다. 제 생각에는 제 구현에 문제가 있거나 제가 이해한 바가 틀린것 같습니다.
    * 혹시 정확한 풀이와 소스코드가 있으신 분은 저한테 알려주시면 감사하겠습니다 ㅎㅎ
---

* 이메일 : eastern7star@gmail.com
