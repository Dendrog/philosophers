# 42 Philosopher

## 개요
C 언어와 pthread를 사용하여 **Dining Philosophers Problem**을 구현한 프로젝트  
멀티스레딩과 동기화를 통해 철학자들이 데드락 없이 식사하도록 구현

## 기능
- N명의 철학자가 테이블에서 사고, 식사, 휴식을 반복
- 포크(fork) 접근을 **mutex**로 동기화
- 철학자의 상태와 식사 횟수, 사고/식사/대기 시간 관리
- 프로그램 종료 시 철학자 상태 출력

## 사용법
```bash
# 컴파일
make

# 실행 예시
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
## 결과
<img width="455" height="467" alt="image" src="https://github.com/user-attachments/assets/e40a6c39-874e-4c93-9208-e732aad164d3" />

## 결과 시각화 (위의 결과와 다른 값)
<img width="1924" height="478" alt="image" src="https://github.com/user-attachments/assets/e20f4e89-b181-4a65-9a91-bd348d21d8e9" />
