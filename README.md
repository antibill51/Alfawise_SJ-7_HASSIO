# Alfawise_SJ-7_HASSIO

## Flashing

For flashing, you have to solder wires like this:

![alt text](https://www.tala-informatique.fr/wiki/images/e/e1/Esp-01.png)

Use U0TXD, U0RXD, GND (and VCC if you dont want to use the diffuser power supply).

Make sure to ground GPIO0 during boot. 

## Installation

You can use the ESPHome add-on from Home Assistant Community Add-ons

## Lovelace card

For lovelace card, you need this HACS Addons : 

- custom:vertical-stack-in-card https://github.com/ofekashery/vertical-stack-in-card
- custom:fan-percent-button-row https://github.com/finity69x2/fan-percent-button-row
- custom:paper-buttons-row https://github.com/jcwillox/lovelace-paper-buttons-row

Lovelace card screenshot :

![alt text](https://raw.githubusercontent.com/antibill51/Alfawise_SJ-7_HASSIO/master/Lovelace/lovelace_card_example.png)

## Contributions are welcome!

If you want to contribute to this please read the [Contribution guidelines](CONTRIBUTING.md)
