import sys
sys.path.append('/home/viet1004/.local/lib/python3.8/site-packages')

import tweepy


consumer_key = ''
consumer_secret = ''
access_token = ''
access_token_secret = ''

search_word = "#klmdcatadbac"
#search_word = "So"

def OAuth():
	try:
		auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
		auth.set_access_token(access_token, access_token_secret)
		return auth
	except Exception as e:
		return None

oauth = OAuth()
api = tweepy.API(oauth)

tweets = tweepy.Cursor(api.search, q = search_word, lang = "en").items(20)

with open("TweetDownload.txt", "w") as filetxt:
	for tweet in tweets:
		filetxt.write(tweet.text)

