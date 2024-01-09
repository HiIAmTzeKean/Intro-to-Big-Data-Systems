import pandas as pd

card_dict = {}
with open('data/card') as f:
    for line in f:
        id, name, _, _ = line.split(",")
        card_dict[id] = name

acc_dict = {}
with open('data/account') as f:
    for line in f:
        id, name, _, _ = line.split(",")
        acc_dict[id] = name
print(f"We have {len(card_dict)} cards and {len(acc_dict)} accounts")

df_acc = pd.read_csv('data/account_to_account', sep=",", names=["src", "tgt","_1", "amt", "strategy","_2", "bus","_3","_4","_5","_6","_7","_8"], header=None)
df_acc = df_acc[["src", "tgt", "amt", "strategy", "bus"]]
df_acc
df_card = pd.read_csv('data/account_to_card', sep=",", names=["src", "tgt","_1", "amt", "strategy","_2", "bus","_3","_4","_5","_6","_7","_8"], header=None)
df_card = df_card[["src", "tgt", "amt", "strategy", "bus"]]
df_card

# Look up names in the corresponding files
df_card["src_name"] = df_card["src"].apply(lambda x: acc_dict[str(x)])
df_card["tgt_name"] = df_card["tgt"].apply(lambda x: card_dict[str(x)])
df_acc["src_name"] = df_acc["src"].apply(lambda x: acc_dict[str(x)])
df_acc["tgt_name"] = df_acc["tgt"].apply(lambda x: acc_dict[str(x)])

# Account to card is 0 and account to account is 1
df_card["type"] = 0
df_acc["type"] = 1
df = pd.concat([df_card, df_acc])

df["amt"] = df["amt"].apply(lambda x: int(float(x)))
df["strategy"] = df["strategy"].apply(lambda x: int(x.replace("strategy_name-", "")))
df["bus"] = df["bus"].apply(lambda x: int(x.replace("buscode", "")))
# Drop rows that are completely similar
df = df.drop_duplicates()
# Make edge embeddings
df["edge"] = df["src_name"].astype(str) + "-" + df["tgt_name"].astype(str) + "-" + df["type"].astype(str) + "-" + df["strategy"].astype(str) + "-" + df["bus"].astype(str) + "-" + df["amt"].astype(str)
# Count the freuquency of edge embeddings
df["edge_count"] = df.groupby(['edge'])["src"].transform('count')
# Remove edges that are not frequent enough
df = df[df["edge_count"] >= 10000]
# Save dataframe as input file
df[["src", "tgt", "amt", "strategy", "bus", "src_name", "tgt_name", "type"]].to_csv("data/full.csv", index=False)