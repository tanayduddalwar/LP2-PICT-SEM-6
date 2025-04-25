class EmployeeExpertSystem:
    def __init__(self):
        self.criteria={
                "Punctuality":0,
                "Task Completion":0,
                "Quality of work":0,
                "Teamwork":0,
                "Communication":0,
                "Peer Feedback":0,
            }
    def evaluate_employee(self, total_score):
        if total_score >= 22:
            return "Excellent", "Eligible for promotion or leadership opportunities."
        elif total_score >= 15:
            return "Good", "Consider recognition, reward, and upskilling."
        else:
            return "Needs Improvement", "Recommend training, mentorship, and performance improvement plans."

    def display_results(self,total_score,level,advice):
        print(f"\nEmployee Evaluation Results:")
        print(f"Total Score: {total_score}")
        print(f"Performance Level: {level}")
        print(f"Advice: {advice}")
    def run_system(self):
        print("Employee Evaluation System")
        scores={}
        print("Please rate the employee on a scale of 1 to 5 for the following criteria:")
        for i in self.criteria:
            while True:
                    score = int(input(f"{i}: "))
                    if score < 1 or score > 5:
                        raise ValueError("Score must be between 1 and 5.")
                    scores[i] = score
                    break
        total=0
        for i in scores:
            total += scores[i]
        level,advice = self.evaluate_employee(total)   
        self.display_results(total,level,advice)
        print("\nThank you for using the Employee Evaluation System!") 

if __name__ == "__main__":
    employee_system = EmployeeExpertSystem()
    employee_system.run_system()             
                



    