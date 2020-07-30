import telebot
import requests
from bs4 import BeautifulSoup

token = ''  # token from BotFather
bot = telebot.TeleBot(token)

headers = {
    'accept': '*/*',
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                  'Chrome/78.0.3904.70 Safari/537.36'
}
weather_url = 'https://pogodnik.com/21364-pogoda-v-natalino-krasnogradskij-rajon-harkovskaya-oblast-ukraina'
currencies_url = 'https://privatbank.ua/'


def scrap_weather(url, header):
    """Scraping weather from url"""
    session = requests.session()
    request = session.get(url, headers=header)
    if request.status_code == 200:
        soup = BeautifulSoup(request.content, 'html.parser')

        # get the necessary elements from the soup
        weather = str(soup.find('p', attrs={'v-text': 'condition'}).string).replace('\n', '').replace(' ', '').lower()
        temperature = str(soup.find('span', attrs={'v-text': 'temperature'}).string).replace(' ', '')
        humidity = str(soup.find('span', attrs={'v-text': 'humidity'}).string).replace(' ', '')

        session.close()
        return weather, temperature, humidity
    else:
        return False


def scrap_currencies(url, header):
    """Scraping exchange rates from bank page"""
    session = requests.session()
    request = session.get(url, headers=header)
    if request.status_code == 200:
        soup = BeautifulSoup(request.content, 'html.parser')

        # get the necessary elements from the soup
        usd_buy = str(soup.find('td', id='USD_buy').string).replace('\n', '').replace(' ', '')
        usd_sell = str(soup.find('td', id='USD_sell').string).replace('\n', '').replace(' ', '')
        eur_buy = str(soup.find('td', id='EUR_buy').string).replace('\n', '').replace(' ', '')
        eur_sell = str(soup.find('td', id='EUR_sell').string).replace('\n', '').replace(' ', '')
        rub_buy = str(soup.find('td', id='RUB_buy').string).replace('\n', '').replace(' ', '')
        rub_sell = str(soup.find('td', id='RUB_sell').string).replace('\n', '').replace(' ', '')

        session.close()
        return usd_buy, usd_sell, eur_buy, eur_sell, rub_buy, rub_sell
    else:
        return False


result_weather = scrap_weather(weather_url, headers)
currencies = scrap_currencies(currencies_url, headers)


@bot.message_handler(commands=['start'])
def start_message(message):
    """Sends a greeting when the bot receives a start command"""
    username = message.from_user.first_name
    bot.send_message(message.chat.id, f'Hi, {username}, I am a bot created by this guy @rugalyov21 🤖 \n \n'
                                      f'Available commands can be found by clicking /command')


@bot.message_handler(commands=['command'])
def command_message(message):
    """Sends a list of available commands installed in the BotFather"""
    bot.send_message(message.chat.id, '/start - Say Hi \n/weather - Weather in Ukraine \n/command - '
                                      'Commands for control\n/currencies - Currency rates')


@bot.message_handler(commands=['weather'])
def weather_message(message):
    """sends weather data"""
    if not result_weather:
        bot.send_message(message.chat.id, 'Not available now')
    else:
        bot.send_message(message.chat.id, f'In Ukraine now {result_weather[1]}°C,\n'
                                          f'Humidity {result_weather[2]}%,\n'
                                          f'in the sky {result_weather[0]}\n')


@bot.message_handler(commands=['currencies'])
def currencies_message(message):
    """sends data on exchange rates"""
    if not currencies:
        bot.send_message(message.chat.id, 'Not available now')
    else:
        bot.send_message(message.chat.id, f'Now the bank has such exchange rates🏦: \n\n'
                                          f'dollar :\n Buy {currencies[0]}    |    sale {currencies[1]}\n'
                                          f'euro :\n Buy {currencies[2]}    |    sale {currencies[3]}\n'
                                          f'ruble:\n Buy {currencies[4]}    |    sale {currencies[5]}\n')


@bot.message_handler(content_types=['sticker'])
def sticker_message(message):
    """Respond to a sticker from a user"""
    bot.send_message(message.chat.id, 'Nice stiker👍')


bot.polling(none_stop=True)
