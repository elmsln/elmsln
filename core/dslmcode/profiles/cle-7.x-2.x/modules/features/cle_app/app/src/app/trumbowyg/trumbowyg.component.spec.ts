/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { TrumbowygComponent } from './trumbowyg.component';

describe('TrumbowygComponent', () => {
  let component: TrumbowygComponent;
  let fixture: ComponentFixture<TrumbowygComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ TrumbowygComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(TrumbowygComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
