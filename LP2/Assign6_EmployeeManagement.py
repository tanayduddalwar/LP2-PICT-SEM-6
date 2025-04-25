class EmployeeManagementSystem:
    def __init__(self):
        self.criteria = {
            "Punctuality": 0,
            "Task Completion": 0,
            "Quality of work": 0,
            "TeamWork": 0,
            "Peer Review": 0,
            "Communication": 0
        }

    def evaluate(self, total_score):
        if total_score > 22:
            return "Excellent", "Eligible for promotion"
        elif total_score >= 15:
            return "Good", "Consider recognition"
        else:
            return "Needs Improvement", "Recommend training"

    def run(self):
        num_employees = int(input("Enter the number of employees you want to evaluate: "))
        
        for j in range(num_employees):
            scores = {}
            name = input("Enter employee's name: ")
            print(f"Evaluating {name}...")
            print("Enter the score between 1 to 5 for each criterion")

            for i in self.criteria:
                while True:
                    try:
                        score = int(input(f"{i}: "))
                        if 1 <= score <= 5:
                            scores[i] = score
                            break
                        else:
                            print("Enter score between 1 to 5")
                    except ValueError:
                        print("Invalid input. Please enter a numeric value.")

            total_score = 0
            for i in scores:
                total_score += scores[i]

            level, advice = self.evaluate(total_score)
            print(f"\nEvaluation Results for {name}")
            print(f"Total Score: {total_score}")
            print(f"Level: {level}")
            print(f"Advice: {advice}")
            print("-" * 40)

if __name__ == "__main__":
    name = EmployeeManagementSystem()
    name.run()
