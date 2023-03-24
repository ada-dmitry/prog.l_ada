import psycopg2
import wget
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
# Парсер и загрузчик в БД//Антипенко Дмитрий
connection = psycopg2.connect(host='localhost', dbname='PythonDB', user='postgres', password='Q1w2e3r4')

cursor = connection.cursor()

creat_qwery = """ create table Parser 
    (id serial primary key, page_name varchar(100), price varchar(10), priceDis varchar(30), mark varchar(10), scr varchar(100))"""

cursor.execute(creat_qwery)
connection.commit()

driver = Service('D:\teach\Prog\chromedriver.exe') 
browser = webdriver.Chrome(service=driver)
browser.get('https://amwine.ru/catalog/igristoe_vino_i_shampanskoe/igristoe_vino/')
html_code = browser.page_source
b_soup = BeautifulSoup(html_code, 'lxml')
name = b_soup.find_all('a', class_="catalog-list-item__title js-product-detail-link")
price = b_soup.find_all('span', class_="middle_price")
priceDis = b_soup.find_all('span', class_="baseoldprice")
mark = b_soup.find_all('span', class_="product-rating__rating")
pictures = b_soup.find_all('div', class_="catalog-list-item__img-wrapper")

for i in range(15):
    url = 'https://amwine.ru'+pictures[i].find('a').find('img').attrs['data-src']
    filename = f"Programming\\23.03\img\{i}.jpg"
    print(filename)
    wget.download(url, filename)
    ins_qwery = f"""insert into public.Parser(page_name, price, priceDis, mark, scr) values ('{name[i].text}', '{price[i].text}', '{priceDis[i].text}',  '{mark[i].text}', '{filename}')"""
    cursor.execute(ins_qwery)
    connection.commit()




cursor.close()

connection.close()