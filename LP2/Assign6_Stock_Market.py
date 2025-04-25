class StockTradingExpertSystem:
    def __init__(self):
        self.trading_profiles = {
            "Seasoned Trader": {
                "behaviors": {
                    "diversified portfolio": 3,
                    "defined stop loss": 3,
                    "uses indicators": 2,
                    "technical analysis": 2,
                    "options hedging": 2
                },
                "issues": ["market volatility", "sector rotation"],
                "recommendation": "Keep refining your system. Consider algo strategies, backtesting frameworks, or quantitative analysis."
            },
            "Intermediate Trader": {
                "behaviors": {
                    "swing trading": 2,
                    "trend following": 2,
                    "fundamental analysis": 1,
                    "uses mobile app": 1
                },
                "issues": ["stop loss hit often", "missed entry points"],
                "recommendation": "Backtest your entries and explore better risk-reward setups using tools like TradingView or Zerodha’s Streak."
            },
            "Beginner Trader": {
                "behaviors": {
                    "fomo buying": -3,
                    "no stop loss": -3,
                    "random entry": -2,
                    "influencer-based decisions": -2
                },
                "issues": ["frequent losses", "emotional trading"],
                "recommendation": "Focus on risk management and trading psychology. Start with paper trading or index ETFs before real trades."
            }
        }

        self.risk_levels = {
            "low": "Your risk profile is healthy. Focus on consistency and refining your system.",
            "moderate": "Your trades show promise but risk leaks exist. Manage positions carefully.",
            "high": "Risk management is poor. You are at high risk of capital erosion."
        }

        self.trading_consultants = {
            "Derivatives": {
                "Seasoned Trader": ["Karan Bansal – Derivatives & Options Strategist"],
                "Intermediate Trader": ["Anita Deshmukh – Swing Options Coach"]
            },
            "Equity": {
                "Beginner Trader": ["Mehul Shah – Equity Risk Mentor"],
                "Intermediate Trader": ["Naina Verma – Portfolio Building Guide"]
            },
            "Crypto": {
                "Intermediate Trader": ["Jay Bhagat – Web3 Strategy Analyst"],
                "Beginner Trader": ["Ritu Garg – Crypto Volatility Educator"]
            }
        }

    def evaluate_trading_behaviors(self, behaviors, issues):
        profile_scores = {}

        for profile, details in self.trading_profiles.items():
            score = 0
            matched_behaviors = []
            matched_issues = list(set(issues) & set(details["issues"]))

            for behavior in behaviors:
                if behavior in details["behaviors"]:
                    score += details["behaviors"][behavior]
                    matched_behaviors.append(behavior)

            if matched_issues:
                score -= len(matched_issues)

            profile_scores[profile] = {
                "score": score,
                "matched_behaviors": matched_behaviors,
                "matched_issues": matched_issues,
                "recommendation": details["recommendation"]
            }

        return profile_scores

    def determine_risk_level(self, score):
        if score >= 6:
            return "low"
        elif 2 <= score < 6:
            return "moderate"
        else:
            return "high"

    def find_consultants(self, profile, asset_class):
        asset_profiles = self.trading_consultants.get(asset_class, {})
        return asset_profiles.get(profile, ["No consultant found for this combination."])

    def run_system(self):
        print("\n📊 Welcome to the Stock Market Trading Expert System")
        print("Enter your trading behaviors (comma separated):")
        behaviors_input = input().strip().lower().split(",")

        print("\nEnter your major trading challenges (or 'none'):")
        issue_input = input().strip().lower()
        issues_input = issue_input.split(",") if issue_input != "none" else []

        behaviors = [b.strip() for b in behaviors_input if b.strip()]
        issues = [c.strip() for c in issues_input if c.strip()]

        profiles = self.evaluate_trading_behaviors(behaviors, issues)
        total_score = max([details["score"] for details in profiles.values()])
        risk_level = self.determine_risk_level(total_score)

        if profiles:
            best_fit = max(profiles.items(), key=lambda x: x[1]['score'])
            profile_name, details = best_fit
            print(f"\n📌 Trading Profile: {profile_name}")
            print(f"📈 Recommendation: {details['recommendation']}")

            asset_class = input("\n📂 Enter your primary asset class (Equity, Derivatives, Crypto): ").strip()
            print(f"\n🧠 Suggested Consultants for {asset_class} - {profile_name}:")
            print(", ".join(self.find_consultants(profile_name, asset_class)))

            print(f"\n⚠️ Risk Level: {risk_level.capitalize()} - {self.risk_levels[risk_level]}")
        else:
            print("\n⚠️ Could not evaluate trading maturity. Please check your input.")

if __name__ == "__main__":
    system = StockTradingExpertSystem()
    system.run_system()
