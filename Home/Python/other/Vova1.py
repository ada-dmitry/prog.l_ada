from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
import psycopg2
import wget

browser = webdriver.Chrome(service=Service('C:\Desktop\exe\chromedriver.exe'))
browser.get('https://flawery.ru/moscow/bouquets/event-yanvary25/')
soup = BeautifulSoup(browser.page_source, "lxml")
Name = soup.find_all(attrs={"class": "catalog_title"})
Price = soup.find_all(attrs={"class": "catalog_price_now"})
Delivery_Time = soup.find_all(attrs={"class": "catalog_express"})
Delivery_Price = soup.find_all(attrs={"class": "catalog_delivery"})
Image = soup.find_all('div', class_="catalog_item catalog_item_popup")

connection = psycopg2.connect(host='localhost', dbname='FHWDB', user='postgres', password='Q1w2e3r4')
cursor = connection.cursor()
create_q = '''CREATE TABLE Parse
(ID serial primary key, Name varchar(100), Price varchar(9), Delivery_Time varchar(25), Delivery_Price varchar(20), src varchar(110))'''
cursor.execute(create_q)
connection.commit()

for j in range(10):
    url = 'https://flawery.ru'+Image[j].find('a').find('img').attrs['src']
    print(url)
    tempf = f'C:\\Users\\user\\Desktop\\FHWDB{j}.jpg'
    wget.download(url, tempf)
    insert_query = f'''INSERT into public.Parse(Name, Price, Delivery_Time, Delivery_Price, scr) values ('{Name[j].text}', '{Price[j].text}', '{Delivery_Time[j].text}', '{Delivery_Price[j].text}', '{tempf}') '''
    cursor.execute(insert_query)
    connection.commit()

cursor.close()
connection.close()