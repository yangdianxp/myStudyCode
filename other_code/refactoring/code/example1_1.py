import traceback
import sys

plays = {
    "hamlet": {"name": "Hamlet", "type": "tragedy"},
    "as-like": {"name": "As You Like It", "type": "comedy"},
    "othello": {"name": "Othello", "type": "tragedy"}
}

invoices = {
    "customer": "BigCo",
    "performances": [
        {
            "playID": "hamlet",
            "audience": 55
        },
        {
            "playID": "as-like",
            "audience": 35
        },
        {
            "playID": "othello",
            "audience": 40
        }
    ]
}

def amountFor(perf, play):
    thisAmount = 0
    if play["type"] == "tragedy":
        thisAmount = 40000
        if perf["audience"] > 30:
            thisAmount += 1000 * (perf["audience"] - 30)
    elif play["type"] == "comedy":
        thisAmount = 30000
        if perf["audience"] > 20:
            thisAmount += 10000 + 500 * (perf["audience"] - 20)
        thisAmount += 300 * perf["audience"]
    else:
        raise NameError("unknown type:{}".format(play["type"]))
    return thisAmount

def statement (invoices, plays):
    totalAmount = 0;
    volumeCredits = 0;
    result = "Statement for {}\n".format(invoices["customer"])
    for perf in invoices["performances"]:
        play = plays[perf["playID"]]

        thisAmount = amountFor(perf, play)
        
        volumeCredits += max(perf["audience"] - 30, 0)
        if "comedy" == play["type"]:
            volumeCredits += round(perf["audience"] / 5)
        result += "  {}: ${} ({} seats)\n".format(play["name"], thisAmount / 100, perf["audience"])
        totalAmount += thisAmount
    result += "Amount owed is ${}\n".format(totalAmount/100)
    result += "You earned ${} credits\n".format(volumeCredits)
    print(result)

def main(argv):
    statement(invoices, plays)

if __name__ == "__main__":
    try:
        main(sys.argv)
    except Exception as result:
        ex_type, ex_val, ex_stack = sys.exc_info()
        print(ex_type)
        print(ex_val)
        for stack in traceback.extract_tb(ex_stack):
            print(stack)
